// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Class.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The class.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// The class.
    /// </summary>
    public class Class : ClassCollection
    {
        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name { get; set; }

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
    }
}