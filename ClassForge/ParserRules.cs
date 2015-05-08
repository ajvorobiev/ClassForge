namespace ClassForge
{
    public static class ParserRules
    {
        public static string PropertyArraySearchPattern = @"(?'Name'[\w+]+\[\])[ \t]?=\s*\{\s*(?'Value'[\w+\$\.\,\\*\/\""\s\-\{\}]+)?\s*\}\;([ \t]?/[\*\/]+[ ]?(?'Remark'[\S ]+))?";

        public static string PropertySearchPattern = @"(?'Name'[\w+]+)[ \t]?=\s*(?'Value'[\w+\$\.\,\\*\/\""\s\-\{\}]+)?\s*\;([ \t]?/[\*\/]+[ ]?(?'Remark'[\S ]+))?";

        public static string PropertyReplacePattern = @"<Parameter Name=""${Name}"" Value=""${Value}"" Remark=""${Remark}"" />";

        public static string ClassSearchPattern = @"(\/\/\/<summary>\s*\/\/\/[ \t]*(?'Remark'.*)\s*\/\/\/</summary>\s*)?class[ \t]+(?'Name'[\S]+)[ \t]*:?[ \t]*(?'Inheritance'[\S]+)?\s*[\{]+";

        public static string ClassReplacePattern = @"<Class Name=""${Name}"" Inheritance=""${Inheritance}"" Remark=""${Remark}"">";

        public static string ClassCloseSearchPattern = @"};";

        public static string ClassReferenceSearchPattern = @"class[ \t]+[\w]+;[\s]*";

        public static string ClassCloseReplacePattern = @"</Class>";

        public static string BlockCommentSearchPattern = @"/\*(?>(?:(?>[^*]+)|\*(?!/))*)\*/";

        public static string LineCommentSearchPattern = @"\/\/.*";

        public static string DefineMultiSearchPattern = @"#define\s+(?'Name'\S+)\s+(?'Value'(?:[ \t\w\$\#\{|=\;\-\.\""\\:}]*\\[\s]+)+[\S\;]*)";

        public static string DefineSearchPattern = @"#define\s+(?'Name'\S+)\s+(?'Value'(?:[ \t\w\$\#\{|=\;\-\.\""\\:}]*))";

        public static string IncludeSearchPattern = @"\#include[ \t]+\""(?'File'[\w+\.]+)\""";
    }
}
