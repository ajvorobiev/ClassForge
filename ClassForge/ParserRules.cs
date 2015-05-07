using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassForge
{
    public static class ParserRules
    {
        //public static string ClassRule = @"(?'Top'class\s(?'Name'[a-zA-Z_\d]+)\s?:?\s?(?'Inherit'[a-zA-Z_\d]+)?\s?\n?\r?[^\{\}]*(((?'Open'\{)[^\{\}]*)+((?'Close-Open'\})[^\{\}]*)+)*(?('Open')(?!)))^([\s]*(?=class))";

        //public static string ClassRuleSolitary = @"(?'Top'class\s(?'Name'[a-zA-Z_\d]+)\s?:?\s?(?'Inherit'[a-zA-Z_\d]+)?\s?\n?\r?[^\{\}]*(((?'Open'\{)[^\{\}]*)+((?'Close-Open'\})[^\{\}]*)+)*(?('Open')(?!)))";

        public static string ClassRule = @"(?'Top'class\s(?'Name'[a-zA-Z_\d]+)\s?:?\s?(?'Inherit'[a-zA-Z_\d]+)?[^\{\}]*(((?'Open'\{)[^\{\}]*)+((?'Close-Open'\})[^\{\}]*)+)*(?('Open')(?!)))^([\s]*(?=class))";

        public static string ClassRuleSolitary = @"(?'Top'class\s(?'Name'[a-zA-Z_\d]+)\s?:?\s?(?'Inherit'[a-zA-Z_\d]+)?[^\{\}]*(((?'Open'\{)[^\{\}]*)+((?'Close-Open'\})[^\{\}]*)+)*(?('Open')(?!)))";

        public static string PropertyRule = @"(?'Name'[\w+\[\]]+)\s?=\s?[\{]*\s?(?'Value'[\w+\$\.\,\\*\/\""\s]+)\}?\;";


    }
}
