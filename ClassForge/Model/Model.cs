// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Model.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   A model represents a whole file
// </summary>
// --------------------------------------------------------------------------------------------------------------------

using System;
using System.Linq;

namespace ClassForge.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// A model represents a whole file
    /// </summary>
    public class Model : ClassCollection
    {
        /// <summary>
        /// The class map.
        /// </summary>
        private Dictionary<string, Class> ClassMap;

        /// <summary>
        /// Initializes a new instance of the <see cref="Model"/> class.
        /// </summary>
        public Model()
        {
            this.Classes = new List<Class>();
            this.ClassMap = new Dictionary<string, Class>();
        }

        /// <summary>
        /// Merges multiple models into this model.
        /// </summary>
        /// <param name="models">
        /// The models.
        /// </param>
        public void MergeFromListOfModels(List<Model> models)
        {
            foreach (Model model in models)
            {
                foreach (Class c in model.Classes)
                {
                    this.MergeClass(this.Classes, c);
                }
            }
        }

        /// <summary>
        /// Merge a class into a list
        /// </summary>
        /// <param name="classList">
        /// The class list.
        /// </param>
        /// <param name="mergeClass">
        /// The class.
        /// </param>
        private void MergeClass(List<Class> classList, Class mergeClass)
        {
            var exClass = classList.FirstOrDefault(c => c.Name == mergeClass.Name);

            if (exClass == null)
            {
                classList.Add(mergeClass);
                try
                {
                    this.ClassMap.Add(mergeClass.Name, mergeClass);
                }
                catch (Exception)
                {
                    //Console.WriteLine("The class named {0} already exists in classmap", mergeClass.Name);
                }

                foreach (var r in mergeClass.Classes)
                {
                    try
                    {
                        this.ClassMap.Add(r.Name, r);
                    }
                    catch (Exception)
                    {
                        //Console.WriteLine("The class named {0} already exists in classmap", r.Name);
                    }
                }
            }
            else
            {
                foreach (var cd in mergeClass.Classes)
                {
                    // only add the class if it doesnt exist yet
                    if (exClass.Classes.FirstOrDefault(r => r.Name == cd.Name) == null)
                    {
                        exClass.Classes.Add(cd);
                        try
                        {
                            this.ClassMap.Add(cd.Name, cd);
                        }
                        catch (System.Exception)
                        {
                            
                            //Console.WriteLine("The class named {0} already exists in classmap", cd.Name);
                        }
                    }
                }

                exClass.Properties.AddRange(mergeClass.Properties);
            }

            this.UpdateReferences();
        }

        /// <summary>
        /// Updates the model references
        /// </summary>
        private void UpdateReferences()
        {
            foreach (var cl in this.Classes)
            {
                this.UpdateClassReference(cl, null);
            }
        }

        /// <summary>
        /// Updates the class references.
        /// </summary>
        /// <param name="cl">
        /// The child class.
        /// </param>
        /// <param name="parent">
        /// The parent class.
        /// </param>
        private void UpdateClassReference(Class cl, Class parent)
        {
            cl.ContainmentParent = parent;
            Class inheritanceClass;

            if (this.ClassMap.TryGetValue(cl.Inherits, out inheritanceClass))
            {
                cl.InheritanceClass = inheritanceClass;
                inheritanceClass.InheritanceChildren.Add(cl);
            }

            foreach (var cd in cl.Classes)
            {
                this.UpdateClassReference(cd, cl);
            }
        }
    }
}