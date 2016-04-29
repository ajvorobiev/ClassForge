// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Property.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The property
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge.Model
{
    using System;

    /// <summary>
    /// The property
    /// </summary>
    public class Property
    {
        public Property()
        {
            this.Iid = Guid.NewGuid();
        }

        /// <summary>
        /// Gets or sets the unique id.
        /// </summary>
        public Guid Iid { get; set; }

        /// <summary>
        /// Gets or sets the remark.
        /// </summary>
        /// <value>
        /// The remark.
        /// </value>
        public string Remark { get; set; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>
        /// The name.
        /// </value>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the value.
        /// </summary>
        /// <value>
        /// The value.
        /// </value>
        public string Value { get; set; }

        /// <summary>
        /// Gets or sets the parent class iid.
        /// </summary>
        public Guid ParentClassIid { get; set; }
    }
}