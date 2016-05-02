namespace ClassForge.Model
{
    /// <summary>
    /// Header for the dereferenced model output.
    /// </summary>
    public class DereferencedHeader
    {
        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the version.
        /// </summary>
        public string Version { get; set; }

        /// <summary>
        /// Gets or sets the description.
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the top level filters.
        /// </summary>
        public string TopLevelFilters { get; set; }

        /// <summary>
        /// Gets or sets the bottom level filters.
        /// </summary>
        public string BottomLevelFilters { get; set; }

        /// <summary>
        /// Gets or sets the property filters.
        /// </summary>
        public string PropertyFilters { get; set; }
    }
}
