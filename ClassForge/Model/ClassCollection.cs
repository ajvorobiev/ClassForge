// --------------------------------------------------------------------------------------------------------------------
// <copyright file="ClassCollection.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   A collection of classes
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// A collection of classes
    /// </summary>
    public class ClassCollection : IClassCollection
    {
        /// <summary>
        /// Gets or sets a list of <see cref="Class"/>es
        /// </summary>
        public List<Class> Classes { get; set; }
    }
}
