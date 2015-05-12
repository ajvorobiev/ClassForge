// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Macro.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   A define macro
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge.Model
{
    using System.Collections.Generic;
    using System.Text.RegularExpressions;
    
    /// <summary>
    /// A define macro
    /// </summary>
    public class Macro
    {
        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>
        /// The name.
        /// </value>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the raw text.
        /// </summary>
        /// <value>
        /// The raw text.
        /// </value>
        public string RawText { get; set; }

        /// <summary>
        /// Gets or sets the argument.
        /// </summary>
        /// <value>
        /// The argument.
        /// </value>
        public string Argument { get; set; }

        /// <summary>
        /// Gets or sets the value.
        /// </summary>
        /// <value>
        /// The value.
        /// </value>
        public string Value { get; set; }

        /// <summary>
        /// Gets or sets the arguments.
        /// </summary>
        /// <value>
        /// The arguments.
        /// </value>
        public List<string> Arguments { get; set; }

        /// <summary>
        /// Gets or sets the search pattern.
        /// </summary>
        /// <value>
        /// The search pattern.
        /// </value>
        public string SearchPattern { get; set; }

        /// <summary>
        /// Gets or sets the replace pattern.
        /// </summary>
        /// <value>
        /// The replace pattern.
        /// </value>
        public string ReplacePattern { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="Macro"/> class.
        /// </summary>
        /// <param name="regexMatch">The regex match.</param>
        public Macro(Match regexMatch)
        {
            this.Arguments = new List<string>();

            this.RawText = regexMatch.Value;
            this.Name = regexMatch.Groups["Name"].Value;
            this.Argument = regexMatch.Groups["Argument"].Value;
            this.Value = regexMatch.Groups["Value"].Value;

            this.DeconstructArguments();

            this.ConstructSearchPattern();
            this.ConstructReplacePattern();
        }

        /// <summary>
        /// Deconstructs the arguments.
        /// </summary>
        private void DeconstructArguments()
        {
            if (string.IsNullOrWhiteSpace(this.Argument)) return;

            var args = this.Argument.Split(new[] { ',' });

            foreach (var arg in args)
            {
                this.Arguments.Add(arg.Trim());
            }
        }

        /// <summary>
        /// Constructs the search pattern.
        /// </summary>
        public void ConstructSearchPattern()
        {
            var result = this.Name;

            if (this.Arguments.Count > 0)
            {
                result += @"\((?'arg0'[\S]+)";

                for (int i = 1; i < this.Arguments.Count; i++)
                {
                    result += @"\,(?'arg" + i + @"'[\S]+)";
                }

                result += @"\)";
            }

            this.SearchPattern = result;
        }

        /// <summary>
        /// Constructs the replace pattern.
        /// </summary>
        public void ConstructReplacePattern()
        {
            var result = this.Value;

            for (int i = 0; i < this.Arguments.Count; i++)
            {
                // replace partials
                result = result.Replace("##" + this.Arguments[i] + "##", "${arg" + i + "}");

                result = result.Replace("##" + this.Arguments[i], "${arg" + i + "}");

                result = result.Replace(this.Arguments[i] + "##", "${arg" + i + "}");

                // replace singles
                result = result.Replace(this.Arguments[i], "${arg" + i + "}");
            }

            // replace ending backslash
            result = result.Replace("\\\r\n", "\r\n");

            this.ReplacePattern = result;
        }
    }
}