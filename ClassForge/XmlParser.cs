// --------------------------------------------------------------------------------------------------------------------
// <copyright file="XmlParser.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The class that can parse the incoming xml
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge
{
    using System.IO;
    using System.Xml.Linq;
    using Model;

    /// <summary>
    /// The class that can parse the incoming xml
    /// </summary>
    public class XmlParser
    {
        /// <summary>
        /// Parses the specified XML string.
        /// </summary>
        /// <param name="xmlString">The XML string.</param>
        /// <returns>The model generated from that string</returns>
        public Model.Model Parse(string xmlString)
        {
            this.Document = new StringReader(xmlString);
            
            var model = new Model.Model();
            this.ParseDocument(ref model);
            
            return model;
        }

        /// <summary>
        /// Parses the document.
        /// </summary>
        /// <param name="model">The model.</param>
        private void ParseDocument(ref Model.Model model)
        {
            string readString;

            while ((readString = this.Document.ReadLine()) != null)
            {
                if (readString.Contains("<Class"))
                {
                    var newClass = new Class();
                    var element = XElement.Parse(readString);
                    newClass.Name = element.Attribute("Name").Value;
                    newClass.Inherits = element.Attribute("Inheritance").Value;
                    newClass.Remark = element.Attribute("Remark").Value;
                    this.ParseClass(ref newClass);
                    model.Classes.Add(newClass);
                }
            }
        }

        /// <summary>
        /// Gets or sets the document.
        /// </summary>
        /// <value>
        /// The document.
        /// </value>
        public StringReader Document { get; set; }

        /// <summary>
        /// Parses the class.
        /// </summary>
        /// <param name="store">The store.</param>
        public void ParseClass(ref Class store)
        {
            string readString;

            while ((readString = this.Document.ReadLine()) != null)
            {
                if (readString.Trim().EndsWith(">") && readString.Trim().StartsWith("<"))
                {
                    if (readString.Contains("<Class"))
                    {
                        var newClass = new Class();
                        var element = XElement.Parse(readString);
                        newClass.Name = element.Attribute("Name").Value;
                        newClass.Inherits = element.Attribute("Inheritance").Value;
                        newClass.Remark = element.Attribute("Remark").Value;
                        this.ParseClass(ref newClass);
                        store.Classes.Add(newClass);
                    }
                    else if (readString.Contains("</Class>"))
                    {
                        return;
                    }
                    else if (readString.Contains("<Parameter"))
                    {
                        try
                        {
                            var newProperty = new Property();
                            var element = XElement.Parse(readString);
                            newProperty.Name = element.Attribute("Name").Value;
                            newProperty.Value = element.Attribute("Value").Value;
                            newProperty.Remark = element.Attribute("Remark").Value;
                            newProperty.ParentClassIid = store.Iid;
                            store.Properties.Add(newProperty);
                        }
                        catch (System.Exception ex)
                        {
                            // do nothing, skip this parameter, something obviously went wrong
                        }
                    } 
                }
            }
        }
    }
}
