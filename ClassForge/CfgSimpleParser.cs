using System;
using System.Text.RegularExpressions;
using ClassForge.Model;

namespace ClassForge
{
    using System.IO;

    public class CfgSimpleParser
    {

        public Model.Model Model { get; set; }

        public void Parse(string path)
        {
            var stringText = File.ReadAllText(path);

            this.Model = new Model.Model();

            ParseTextForClasses(stringText);
        }

        public void ParseTextForClasses(string text)
        {
            int innerIndex = 7;

            // Here we call Regex.Match.
            MatchCollection matches = Regex.Matches(text, ParserRules.ClassRule, RegexOptions.Multiline);
            var solitaryMode = false;
            if (matches.Count == 0)
            {
                matches = Regex.Matches(text, ParserRules.ClassRuleSolitary, RegexOptions.Multiline);
                if (matches.Count == 0)
                {
                    return;
                }
                else
                {
                    solitaryMode = true;
                }
            }

            foreach (Match match in matches)
            {
                var newClass = new ClassForge.Model.Class();
                newClass.Name = match.Groups["Name"].Value;
                newClass.Inherits = match.Groups["Inherit"].Value;
                newClass.InternalText = match.Groups["Close"].Value;

                this.ParseClassForClasses(newClass.InternalText, ref newClass);

                this.Model.Classes.Add(newClass);

                // remove the matched class and rerun on the modded text
                var modedText = text.Replace(match.Value, "");
                MatchCollection matchesModded = Regex.Matches(modedText, ParserRules.ClassRule, RegexOptions.Multiline);

                if (matchesModded.Count == 0)
                {
                    matchesModded = Regex.Matches(modedText, ParserRules.ClassRuleSolitary, RegexOptions.Multiline);
                    if (matchesModded.Count != 0)
                    {
                        this.ParseTextForClasses(modedText);
                    }
                }
                else
                {
                    this.ParseTextForClasses(modedText);
                }
            }
        }

        public void ParseClassForClasses(string text, ref Model.Class parentclass)
        {
            // Here we call Regex.Match.
            MatchCollection matches = Regex.Matches(text, ParserRules.ClassRule, RegexOptions.Multiline);

            bool solitaryMode = false;

            if (matches.Count == 0)
            {
                matches = Regex.Matches(text, ParserRules.ClassRuleSolitary, RegexOptions.Multiline);
                if (matches.Count == 0)
                {
                    return;
                }
                else
                {
                    solitaryMode = true;
                }
            }

            foreach (Match match in matches)
            {
                var newClass = new ClassForge.Model.Class();
                newClass.Name = match.Groups["Name"].Value;
                newClass.Inherits = match.Groups["Inherit"].Value;
                newClass.InternalText = match.Groups["Close"].Value;

                parentclass.Classes.Add(newClass);

                this.ParseClassForClasses(newClass.InternalText, ref newClass);

                // remove the matched class and rerun on the modded text
                var modedText = text.Replace(match.Value, "");

                if(!string.IsNullOrWhiteSpace(modedText)) this.ParseClassForClasses(modedText, ref newClass );
                
                
            }
        }
    }
}
