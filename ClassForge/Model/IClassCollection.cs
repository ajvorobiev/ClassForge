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
    }
}
