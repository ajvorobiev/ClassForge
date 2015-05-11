// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Model.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   A model represents a whole file
// </summary>
// --------------------------------------------------------------------------------------------------------------------

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
    }
}