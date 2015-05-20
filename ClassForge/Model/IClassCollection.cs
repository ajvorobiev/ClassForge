// --------------------------------------------------------------------------------------------------------------------
// <copyright file="IClassCollection.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The interface of a class collection
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// The interface of a class collection
    /// </summary>
    public interface IClassCollection
    {
        /// <summary>
        /// Gets or sets the list of <see cref="Class"/>es
        /// </summary>
        List<Class> Classes { get; set; }

        /// <summary>
        /// Gets or sets the name
        /// </summary>
        string Name { get; set; }
    }
}
