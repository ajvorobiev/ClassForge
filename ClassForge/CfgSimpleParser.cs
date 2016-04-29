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
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
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
        public string XmlOutput { get; set; }

        /// <summary>
        /// Gets or sets the folder where the file resides.
        /// </summary>
        public string ScanFolder { get; set; }

        /// <summary>
        /// Gets or sets the list of macros in the document
        /// </summary>
        public List<Macro> Macros { get; set; }

        /// <summary>
        /// Parses a directory, looking for every config.cpp file
        /// </summary>
        /// <param name="directoryPath">The path of the folder</param>
        /// <param name="merge">Indicates whether the <see cref="Model"/>s will be merged into one.</param>
        /// <returns>The collection of models.</returns>
        public List<Model.Model> ParseDirectory(string directoryPath, bool merge = false)
        {
            if (!Directory.Exists(directoryPath))
                throw new ArgumentException("The directory Specified does not exist.", "directoryPath");

            var files = Directory.GetFiles(directoryPath, "config.cpp", SearchOption.AllDirectories);

            var result = new List<Model.Model>();

            foreach (var file in files)
            {
                var model = this.Parse(file);
                result.Add(model);
            }

            if (merge)
            {
                var mergedModel = new Model.Model();
                mergedModel.MergeFromListOfModels(result);

                return new List<Model.Model> { mergedModel };
            }

            return result;
        }

        /// <summary>
        /// Parses the directory and outputs a merged model.
        /// </summary>
        /// <param name="directoryPath">The directory path.</param>
        /// <returns>A single <see cref="Model"/> containing all the classes merged from the directory.</returns>
        public Model.Model ParseDirectoryMerged(string directoryPath)
        {
            return this.ParseDirectory(directoryPath, true)[0];
        }

        /// <summary>
        /// Parses the specified file.
        /// </summary>
        /// <param name="filepath">
        /// The filepath of the file.
        /// </param>
        /// <returns>
        /// The <see cref="Model"/>.
        /// </returns>
        public Model.Model Parse(string filepath)
        {
            if (string.IsNullOrWhiteSpace(filepath))
                throw new ArgumentNullException("filepath");

            var fileInfo = new FileInfo(filepath).Directory;

            if (fileInfo == null)
            {
                throw new NullReferenceException("The file cannot be found.");
            }

            // set the folder of the file to be able to use includes
            this.ScanFolder = fileInfo.FullName;

            // read in initial file
            var stringText = File.ReadAllText(filepath);

            this.ParseIncludes(ref stringText);

            this.ParseMacros(ref stringText);

            this.ParseTextForProperties(ref stringText);
            this.StripReferenceClasses(ref stringText);
            this.ParseTextForClasses(ref stringText);
            

            this.StripEmptyLines(ref stringText);

            this.XmlOutput = stringText;

            var xmlParser = new XmlParser();

            return xmlParser.Parse(stringText);
        }

        public DereferencedModel GetDereferencedModel(Model.Model model)
        {
            return new DereferencedModel(model);
        }

        /// <summary>
        /// Strips empty lines
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void StripEmptyLines(ref string stringText)
        {
            stringText = Regex.Replace(stringText, ParserRules.EmptyLineSearchPattern, string.Empty, RegexOptions.Multiline);
        }

        /// <summary>
        /// Parses the macros
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void ParseMacros(ref string stringText)
        {
            this.Macros = new List<Macro>();
            
            // first do a multiline search
            var matches = Regex.Matches(stringText, ParserRules.DefineMultiSearchPattern);

            foreach (Match match in matches)
            {
                // add the macro
                this.Macros.Add(new Macro(match));

                // delete the original
                stringText = Regex.Replace(stringText, Regex.Escape(match.Value), string.Empty);
            }

            // then do a normal singleline search
            matches = Regex.Matches(stringText, ParserRules.DefineSearchPattern);

            foreach (Match match in matches)
            {
                // add the macro
                this.Macros.Add(new Macro(match));

                // delete the original
                stringText = Regex.Replace(stringText, Regex.Escape(match.Value), string.Empty);
            }

            // once all macros saved do a replace on the macros
            foreach (var macro in this.Macros)
            {
                stringText = Regex.Replace(stringText, macro.SearchPattern, macro.ReplacePattern);
            }
        }

        /// <summary>
        /// Parses and inserts the include preprocessor commands
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void ParseIncludes(ref string stringText)
        {
            var matches = Regex.Matches(stringText, ParserRules.IncludeSearchPattern);

            foreach (Match match in matches)
            {
                // open and load the file
                var filepath = string.Format("{0}\\{1}", this.ScanFolder, match.Groups["File"].Value);

                var replacement = string.Empty;

                if (File.Exists(filepath))
                {
                    replacement = File.ReadAllText(filepath);
                }

                stringText = stringText.Replace(match.Value, replacement);
            }

            // recurse if after all replacement still some are left
            if (Regex.Matches(stringText, ParserRules.IncludeSearchPattern).Count != 0)
                this.ParseIncludes(ref stringText);
        }

        /// <summary>
        /// Strips lose comments
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void StripComments(ref string stringText)
        {
            stringText = Regex.Replace(stringText, ParserRules.BlockCommentSearchPattern, string.Empty);
            stringText = Regex.Replace(stringText, ParserRules.LineCommentSearchPattern, string.Empty);
        }

        /// <summary>
        /// Strips the reference classes
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void StripReferenceClasses(ref string stringText)
        {
            stringText = Regex.Replace(stringText, ParserRules.ClassReferenceSearchPattern, string.Empty);
        }

        /// <summary>
        /// Parses and pepaces the classes
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void ParseTextForClasses(ref string stringText)
        {
            var matches = Regex.Matches(stringText, ParserRules.ClassSearchPattern);

            foreach (Match match in matches)
            {
                string name = match.Groups["Name"].Value;
                string inheritance = match.Groups["Inheritance"].Value;
                string remark = match.Groups["Remark"].Value;

                if (!string.IsNullOrWhiteSpace(remark))
                {
                    remark = this.EscapeStringForXML(remark);
                }

                stringText = Regex.Replace(stringText, Regex.Escape(match.Value), string.Format("<Class Name=\"{0}\" Inheritance=\"{1}\" Remark=\"{2}\"/>\r\n", name, inheritance, remark));
            }

            this.StripComments(ref stringText);
            
            stringText = Regex.Replace(stringText, ParserRules.ClassCloseSearchPattern, ParserRules.ClassCloseReplacePattern);
        }

        /// <summary>
        /// Parses and replaces all Property types
        /// </summary>
        /// <param name="stringText">The text to parse</param>
        private void ParseTextForProperties(ref string stringText)
        {
            var matches = Regex.Matches(stringText, ParserRules.PropertyArraySearchPattern);

            foreach (Match match in matches)
            {
                string name = match.Groups["Name"].Value;
                string value = match.Groups["Value"].Value;
                string remark = match.Groups["Remark"].Value;

                if (!string.IsNullOrWhiteSpace(value))
                {
                    value = this.PretifyArrayValue(value);
                }

                if (!string.IsNullOrWhiteSpace(remark))
                {
                    remark = this.EscapeStringForXML(remark);
                }

                var rgx = new Regex(Regex.Escape(match.Value));
                stringText = rgx.Replace(stringText,
                    string.Format("<Parameter Name=\"{0}\" Value=\"{1}\" Remark=\"{2}\"/>\r\n", name, value, remark), 1);
            }

            matches = Regex.Matches(stringText, ParserRules.PropertySearchPattern);

            foreach (Match match in matches)
            {
                string name = match.Groups["Name"].Value;
                string value = match.Groups["Value"].Value;
                string remark = match.Groups["Remark"].Value;

                if (!string.IsNullOrWhiteSpace(value))
                {
                    value = this.EscapeStringForXML(value);
                }

                if (!string.IsNullOrWhiteSpace(remark))
                {
                    remark = this.EscapeStringForXML(remark);
                }

                var rgx = new Regex(Regex.Escape(match.Value));
                stringText = rgx.Replace(stringText,
                    string.Format("<Parameter Name=\"{0}\" Value=\"{1}\" Remark=\"{2}\"/>\r\n", name, value, remark), 1);
            }
        }

        /// <summary>
        /// Cleans up an array string
        /// </summary>
        /// <param name="value">The value of all array values, delimited by comma</param>
        /// <returns>A clean array string</returns>
        private string PretifyArrayValue(string value)
        {
            var stripped = Regex.Replace(value, ParserRules.LineCommentSearchPattern, string.Empty);
            stripped = stripped.Replace("\r\n", string.Empty);

            var values = stripped.Split(new[] { ',' }).ToList();
            var prettyList = new List<string>();

            foreach (var val in values)
            {
                var prettyVal = val.Trim();
                prettyVal = this.EscapeStringForXML(prettyVal);
                
                prettyList.Add(prettyVal);
            }

            if (prettyList.Count == 1)
            {
                return prettyList[0];
            }

            if (prettyList.Count > 1)
            {
                var prettyString = prettyList[0];

                for (int i = 1; i < prettyList.Count; i++)
                {
                    prettyString += string.Format(", {0}", prettyList[i]);
                }

                return prettyString;
            }

            return null;
        }

        /// <summary>
        /// Escapes special characters for XML
        /// </summary>
        /// <param name="prettyVal">The string to escape</param>
        /// <returns>The escaped string</returns>
        private string EscapeStringForXML(string prettyVal)
        {
            // you need to escape characters correctly for xml
            // "   &quot;
            // '   &apos;
            // <   &lt;
            // >   &gt;
            // &   &amp;
            prettyVal = prettyVal.Replace("&", "&amp;");

            prettyVal = prettyVal.Replace("\"", "&quot;");
            prettyVal = prettyVal.Replace("'", "&apos;");
            prettyVal = prettyVal.Replace("<", "&lt;");
            prettyVal = prettyVal.Replace(">", "&gt;");
            prettyVal = prettyVal.Replace("\\", "&#92;");
            prettyVal = prettyVal.Replace(" ", "&#160;");

            return prettyVal;
        }
    }
}
