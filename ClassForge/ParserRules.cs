using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassForge
{
    public static class ParserRules
    {
        public static string ClassRule = @"class\s([a-zA-Z_\d]+)\s?:?\s?([a-zA-Z_\d]+)?\s?\n?\r?[^\{\}]*(((?'Open'\{)[^\{\}]*)+((?'Close-Open'\})[^\{\}]*)+)*(?('Open')(?!))"; // class\s([a-zA-Z_\d]+)\s?:?\s?([a-zA-Z_\d]+)?\s?\n?\r?[^\{\}]*(((?'Open'\{)[^\{\}]*)+((?'Close-Open'\})[^\{\}]*)+)*(?('Open')(?!))
    }
}
