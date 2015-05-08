// --------------------------------------------------------------------------------------------------------------------
// <copyright file="CfgSimpleParser.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The simple regex config parser.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
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
        /// Gets or sets the folder where the file resides.
        /// </summary>
        public string ScanFolder { get; set; } 

        /// <summary>
        /// Parses the specified file.
        /// </summary>
        /// <param name="path">
        /// The path of the file.
        /// </param>
        public void Parse(string path)
        {
            this.Model = new Model.Model();

            if(string.IsNullOrWhiteSpace(path))
                throw new ArgumentNullException("path");

            var fileInfo = new FileInfo(path).Directory;

            if (fileInfo == null)
            {
                throw new NullReferenceException("The file cannot be found.");
            }

            // set the folder of the file to be able to use includes
            this.ScanFolder = fileInfo.FullName;

            // read in initial file
            var stringText = File.ReadAllText(path);

            this.ParseIncludes(ref stringText);

            this.ParseMacros(ref stringText);

            this.ParseTextForProperties(ref stringText);
            this.StripReferenceClasses(ref stringText);
            this.ParseTextForClasses(ref stringText);
            this.StripComments(ref stringText);
            
            // 4. merge classes
            // 5. deserialize the model
        }

        private void ParseMacros(ref string stringText)
        {
            // first do a multiline search

            stringText = Regex.Replace(stringText, ParserRules.DefineMultiSearchPattern, string.Empty);

            // then do a normal search

            stringText = Regex.Replace(stringText, ParserRules.DefineSearchPattern, string.Empty);
        }

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
            if(Regex.Matches(stringText, ParserRules.IncludeSearchPattern).Count != 0) this.ParseIncludes(ref stringText);
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

            

            //stringText = Regex.Replace(stringText, ParserRules.PropertyArraySearchPattern, ParserRules.PropertyReplacePattern);
            var matches = Regex.Matches(stringText, ParserRules.PropertyArraySearchPattern);

            foreach (Match match in matches)
            {
                string name = match.Groups["Name"].Value;
                string value = match.Groups["Value"].Value;
                string remark = match.Groups["Remark"].Value;

                if(!string.IsNullOrWhiteSpace(value)) 
                {
                    value = this.PretifyArrayValue(value);
                }

                stringText = Regex.Replace(stringText, Regex.Escape(match.Value), string.Format("<Parameter Name=\"{0}\" Value=\"{1}\" Remark=\"{2}\" />", name, value, remark));
            }

            stringText = Regex.Replace(stringText, ParserRules.PropertySearchPattern, ParserRules.PropertyReplacePattern);
        }

        private string PretifyArrayValue(string value)
        {

            var values = value.Split(new char[] {','}).ToList();
            var prettyList = new List<string>();

            foreach (var val in values)
            {
                var prettyVal = val.Trim();
                prettyVal = this.PretifyValue(prettyVal);
                
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

        private string PretifyValue(string prettyVal)
        {
            // you need to escape characters correctly for xml
            //"   &quot;
            //'   &apos;
            //<   &lt;
            //>   &gt;
            //&   &amp;

            prettyVal = prettyVal.Replace("&", "&amp");

            prettyVal = prettyVal.Replace("\"", "&quot");
            prettyVal = prettyVal.Replace("'", "&apos");
            prettyVal = prettyVal.Replace("<", "&lt");
            prettyVal = prettyVal.Replace(">", "&gt");

            return prettyVal;
        }
    }
}
