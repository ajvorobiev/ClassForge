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
        /// Gets or sets the internal text.
        /// </summary>
        public string InternalText { get; set; }

        /// <summary>
        /// Gets or sets the internal properties.
        /// </summary>
        public string InternalProperties { get; set; }

        /// <summary>
        /// Gets or sets the full code.
        /// </summary>
        public string FullCode { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="Class"/> class.
        /// </summary>
        public Class()
        {
            this.Classes = new List<Class>();
        }

        /// <summary>
        /// Outputs a visualization of the class
        /// </summary>
        /// <param name="level">
        /// The level of indentation.
        /// </param>
        /// <param name="deep">
        /// The deep.
        /// </param>
        /// <returns>
        /// The <see cref="Class"/> in the form of "-- name : inheritance"
        /// </returns>
        public string StringOutput(int level, bool deep = false)
        {
            var indent = string.Empty;

            for (int i = 0; i < level; i++)
            {
                indent += "-";
            }

            var inheritance = string.IsNullOrWhiteSpace(this.Inherits)
                ? string.Empty
                : string.Format(" : {0}", this.Inherits);

            return string.Format("{0} {1}{2}\n{3}", indent, this.Name, inheritance, deep ? this.InternalText : string.Empty);
        }
    }
}