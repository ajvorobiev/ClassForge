using System.Text.RegularExpressions;
using ClassForge.Model;

namespace ClassForge
{
    using System.IO;

    public class CfgSimpleParser
    {
        public void Parse(string path)
        {
            var stringText = File.ReadAllText(path);

            var model = new Model.Model();

            ParseTextForClasses(stringText, ref model);
        }

        public void ParseTextForClasses(string text, ref Model.Model model)
        {
            // Here we call Regex.Match.
            MatchCollection matches = Regex.Matches(text, ParserRules.ClassRule,
                RegexOptions.IgnoreCase);

            foreach (Match match in matches)
            {
                var newClass = new ClassForge.Model.Class();
                newClass.Name = match.Groups[1].Value;
                newClass.Inherits = match.Groups[2].Value;
                newClass.InternalText = match.Groups[3].Value;

                ParseClassForClasses(newClass.InternalText, ref newClass);

                model.Classes.Add(newClass);
            }
        }

        public void ParseClassForClasses(string text, ref Model.Class parentclass)
        {
            // Here we call Regex.Match.
            MatchCollection matches = Regex.Matches(text, ParserRules.ClassRule,
                RegexOptions.IgnoreCase);

            foreach (Match match in matches)
            {
                var newClass = new ClassForge.Model.Class();
                newClass.Name = match.Groups[1].Value;
                newClass.Inherits = match.Groups[2].Value;
                newClass.InternalText = match.Groups[3].Value;

                ParseClassForClasses(newClass.InternalText, ref newClass);

                parentclass.Classes.Add(newClass);
            }
        }
    }
}
