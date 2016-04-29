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
    using Newtonsoft.Json;

    /// <summary>
    /// A collection of classes
    /// </summary>
    public class ClassCollection : IClassCollection
    {
        /// <summary>
        /// Gets or sets a list of <see cref="Class"/>es
        /// </summary>
        [JsonIgnore]
        public List<Class> Classes { get; set; }

        /// <summary>
        /// Gets or sets the name
        /// </summary>
        public string Name { get; set; }
    }
}
