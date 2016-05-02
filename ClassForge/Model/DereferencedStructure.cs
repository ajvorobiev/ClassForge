namespace ClassForge.Model
{
    using Newtonsoft.Json;

    /// <summary>
    /// Holds the full dereferenced model necessary for export.
    /// </summary>
    public class DereferencedStructure
    {
        /// <summary>
        /// Deserializes the json into this object.
        /// </summary>
        /// <param name="json">The json to deserialize.</param>
        /// <returns>An instance of <see cref="DereferencedStructure"/> containing the deserialized information.</returns>
        public static DereferencedStructure FromJson(string json)
        {
            return JsonConvert.DeserializeObject<DereferencedStructure>(json);
        }

        /// <summary>
        /// Gets or sets the header.
        /// </summary>
        public DereferencedHeader Header { get; set; }

        /// <summary>
        /// Gets or sets the model.
        /// </summary>
        public DereferencedModel Model { get; set; }
    }
}
