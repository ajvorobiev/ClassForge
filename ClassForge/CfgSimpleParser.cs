// --------------------------------------------------------------------------------------------------------------------
// <copyright file="CfgSimpleParser.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The simple regex config parser.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

using GOLD;

namespace ClassForge
{
    using System.IO;
    using System.Text.RegularExpressions;
    using Model;

    /// <summary>
    /// The simple regex config parser.
    /// </summary>
    public class CfgSimpleParser
    {
        /// <summary>
        /// Gets or sets the model.
        /// </summary>
        public Model.Model Model { get; set; }

        /// <summary>
        /// Parses the specified file.
        /// </summary>
        /// <param name="path">
        /// The path of the file.
        /// </param>
        public void Parse(string path)
        {
            var stringText = File.ReadAllText(path);

            this.Model = new Model.Model();

            // TODO
            // 1. parse includes
            // 2. parse macros

            this.ParseTextForProperties(ref stringText);
            this.StripReferenceClasses(ref stringText);
            this.ParseTextForClasses(ref stringText);
            this.StripComments(ref stringText);
            
            // 4. merge classes
            // 5. deserialize the model
        }

        private void StripComments(ref string stringText)
        {
            stringText = Regex.Replace(stringText, ParserRules.BlockCommentSearchPattern, string.Empty);
            stringText = Regex.Replace(stringText, ParserRules.LineCommentSearchPattern, string.Empty);
        }

        private void StripReferenceClasses(ref string stringText)
        {
            stringText = Regex.Replace(stringText, ParserRules.ClassReferenceSearchPattern, string.Empty);
        }

        private void ParseTextForClasses(ref string stringText)
        {
            stringText = Regex.Replace(stringText, ParserRules.ClassSearchPattern, ParserRules.ClassReplacePattern);
            stringText = Regex.Replace(stringText, ParserRules.ClassCloseSearchPattern, ParserRules.ClassCloseReplacePattern);
        }

        private void ParseTextForProperties(ref string stringText)
        {
            // TODO: some manipulation of arrays necessary
            stringText = Regex.Replace(stringText, ParserRules.PropertySearchPattern, ParserRules.PropertyReplacePattern);
        }

    }
}
