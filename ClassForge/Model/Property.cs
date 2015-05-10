namespace ClassForge.Model
{
    using System.Xml.Serialization;

    /// <summary>
    /// The property
    /// </summary>
    public class Property
    {
        /// <summary>
        /// Gets or sets the remark.
        /// </summary>
        /// <value>
        /// The remark.
        /// </value>
        [XmlAttribute]
        public string Remark { get; set; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>
        /// The name.
        /// </value>
        [XmlAttribute]
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the value.
        /// </summary>
        /// <value>
        /// The value.
        /// </value>
        [XmlAttribute]
        public string Value { get; set; }
    }
}