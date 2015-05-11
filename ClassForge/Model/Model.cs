// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Model.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   A model represents a whole file
// </summary>
// --------------------------------------------------------------------------------------------------------------------

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
        /// Initializes a new instance of the <see cref="Model"/> class.
        /// </summary>
        public Model()
        {
            this.Classes = new List<Class>();
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
            }
            else
            {
                exClass.Classes.AddRange(mergeClass.Classes);

                //foreach (var cd in mergeClass.Classes)
                //{
                //    if (exClass.Classes.FirstOrDefault(r => r.Name == cd.Name) == null)
                //    {
                //        exClass.Classes.Add(cd);
                //    }
                //}

                exClass.Properties.AddRange(mergeClass.Properties);
            }
        }
    }
}