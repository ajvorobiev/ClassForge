// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Class.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The class.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

using System;

namespace ClassForge.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// The class.
    /// </summary>
    public class Class : ClassCollection
    {
        /// <summary>
        /// The class map.
        /// </summary>
        private Dictionary<string, Class> ClassMap;

        /// <summary>
        /// Gets or sets the name of the parent class.
        /// </summary>
        public string Inherits { get; set; }

        /// <summary>
        /// Gets or sets the containment parent.
        /// </summary>
        public Class ContainmentParent { get; set; }

        /// <summary>
        /// Gets or sets the inheritance class.
        /// </summary>
        public Class InheritanceClass { get; set; }

        /// <summary>
        /// Gets or sets the inheritance children.
        /// </summary>
        public List<Class> InheritanceChildren { get; set; } 

        /// <summary>
        /// Gets or sets the remark
        /// </summary>
        public string Remark { get; set; }

        /// <summary>
        /// Gets or sets the list of <see cref="Property"/>'s
        /// </summary>
        public List<Property> Properties { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="Class"/> class.
        /// </summary>
        public Class()
        {
            this.Classes = new List<Class>();
            this.Properties = new List<Property>();
            this.InheritanceChildren = new List<Class>();
        }

        /// <summary>
        /// Updates the model references
        /// </summary>
        public void UpdateReferences()
        {
            this.ClassMap = new Dictionary<string, Class>();

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
            try
            {
                this.ClassMap.Add(cl.Name, cl);
            }
            catch (Exception ex)
            {
                //Console.WriteLine("The class named {0} already exists in classmap", cd.Name);
            }

            cl.ContainmentParent = parent;
            Class inheritanceClass;

            if (this.ClassMap.TryGetValue(cl.Inherits, out inheritanceClass))
            {
                cl.InheritanceClass = inheritanceClass;
                if (!inheritanceClass.InheritanceChildren.Contains(cl))
                {
                    inheritanceClass.InheritanceChildren.Add(cl);
                }
            }

            foreach (var cd in cl.Classes)
            {
                cd.UpdateReferences();
            }
        }
    }
}