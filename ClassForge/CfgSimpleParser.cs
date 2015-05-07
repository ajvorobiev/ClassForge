// --------------------------------------------------------------------------------------------------------------------
// <copyright file="CfgSimpleParser.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The simple regex config parser.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

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

            this.ParseTextForProperties(stringText);

            //this.ParseTextForClasses(stringText);
        }

        private void ParseTextForProperties(string stringText)
        {
            var matches = Regex.Matches(stringText, ParserRules.PropertyRule, RegexOptions.IgnoreCase);
            <Parameter Name="${Name}" Value="${Value}" />
            foreach (var match in matches)
            {
                
            }
        }

        /// <summary>
        /// Parses the text directly to the top level model
        /// </summary>
        /// <param name="text">
        /// The text.
        /// </param>
        public void ParseTextForClasses(string text)
        {
            // Here we call Regex.Match.
            var matches = Regex.Matches(text, ParserRules.ClassRule, RegexOptions.Multiline);
            
            if (matches.Count == 0)
            {
                matches = Regex.Matches(text, ParserRules.ClassRuleSolitary, RegexOptions.Multiline);
                if (matches.Count == 0)
                {
                    return;
                }
            }

            foreach (Match match in matches)
            {
                var newClass = new Class
                {
                    Name = match.Groups["Name"].Value,
                    Inherits = match.Groups["Inherit"].Value,
                    InternalText = match.Groups["Close"].Value,
                    FullCode = match.Groups["Top"].Value
                };

                this.ParseClassForClasses(newClass.InternalText, ref newClass);

                this.Model.Classes.Add(newClass);

                // remove the matched class and rerun on the modded text
                var moddedText = text.Replace(newClass.FullCode, "");

                if (!string.IsNullOrWhiteSpace(moddedText)) this.ParseTextForClasses(moddedText);
            }
        }

        /// <summary>
        /// Parses a single class for classes.
        /// </summary>
        /// <param name="text">
        /// The text.
        /// </param>
        /// <param name="parentclass">
        /// The parent <see cref="Class"/>.
        /// </param>
        public void ParseClassForClasses(string text, ref Class parentclass)
        {
            // Here we call Regex.Match.
            var matches = Regex.Matches(text.TrimEnd(), ParserRules.ClassRule, RegexOptions.Multiline);

            if (matches.Count == 0)
            {
                matches = Regex.Matches(text, ParserRules.ClassRuleSolitary, RegexOptions.Multiline);
                if (matches.Count == 0)
                {
                    return;
                }
            }

            foreach (Match match in matches)
            {
                var newClass = new Class
                {
                    Name = match.Groups["Name"].Value,
                    Inherits = match.Groups["Inherit"].Value,
                    InternalText = match.Groups["Close"].Value,
                    FullCode = match.Groups["Top"].Value
                };

                this.ParseClassForClasses(newClass.InternalText, ref newClass);

                parentclass.Classes.Add(newClass);

                // remove the matched class and rerun on the modded text
                var moddedText = text.Replace(newClass.FullCode, "");

                if (!string.IsNullOrWhiteSpace(moddedText)) this.ParseClassForClasses(moddedText, ref parentclass);
            }
        }
    }
}
