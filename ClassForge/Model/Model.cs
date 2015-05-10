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