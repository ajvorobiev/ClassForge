// --------------------------------------------------------------------------------------------------------------------
// <copyright file="ParserRules.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The regex rules for the parser
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge
{
    /// <summary>
    /// The regex rules for the parser
    /// </summary>
    public static class ParserRules
    {
        /// <summary>
        /// The property array search pattern
        /// </summary>
        public static string PropertyArraySearchPattern = @"(?'Name'[\w_]+\[\])[ \t]*\+?=\s*([//\w\s]+)?\{\s*(?'Value'[\w+\$\.\,\\*\/\""\s\-\{\}\(\)\[\]\'\?]+)?\s*\}\;([ \t]?\/[\*\/]+[ ]?(?'Remark'[\S ]+))?";

        /// <summary>
        /// The property search pattern
        /// </summary>
        public static string PropertySearchPattern = @"(?'Name'[\w_]+)[ \t]*=\s*(?'Value'[\w+\$\.\,\\*\/\""\s\-\{\}\(\)\[\]\'\?]+)?\s*\;([ \t]*\/[\*\/]+[ ]?(?'Remark'[\S ]+))?";

        /// <summary>
        /// The property replace pattern
        /// </summary>
        public static string PropertyReplacePattern = @"<Parameter Name=""${Name}"" Value=""${Value}"" Remark=""${Remark}""></Parameter>";

        /// <summary>
        /// The class search pattern
        /// </summary>
        public static string ClassSearchPattern = @"(\/\/\/<summary>\s*\/\/\/[ \t]*(?'Remark'.*)\s*\/\/\/</summary>\s*)?class[ \t]+(?'Name'[\w_]+)[ \t]*:?[ \t]*(?'Inheritance'[\w_]+)?(\s*\/\/.*)?\s*[\{]+";

        /// <summary>
        /// The class replace pattern
        /// </summary>
        public static string ClassReplacePattern = @"<Class Name=""${Name}"" Inheritance=""${Inheritance}"" Remark=""${Remark}""/>";

        /// <summary>
        /// The class closing search pattern
        /// </summary>
        public static string ClassCloseSearchPattern = @"};";

        /// <summary>
        /// The class reference search pattern
        /// </summary>
        public static string ClassReferenceSearchPattern = @"[//]*class[ \t]+[\w]+;[\s]*";

        /// <summary>
        /// The class close replace pattern
        /// </summary>
        public static string ClassCloseReplacePattern = @"</Class>";

        /// <summary>
        /// The block comment search pattern
        /// </summary>
        public static string BlockCommentSearchPattern = @"/\*(?>(?:(?>[^*]+)|\*(?!/))*)\*/";

        /// <summary>
        /// The line comment search pattern
        /// </summary>
        public static string LineCommentSearchPattern = @"\/\/.*";

        /// <summary>
        /// The define multi search pattern
        /// </summary>
        public static string DefineMultiSearchPattern = @"#define\s+(?'Name'[\w+]+)(\((?'Argument'[\S]*)\))?\s+(?'Value'(?:[ \S\t\d\w\$\#\{_\,\+\*\/\\\=\;\-\.\""\\:\}\)\(]*\\[\s]+)+[\w _\=\#\;\""\}]+)";

        /// <summary>
        /// The define search pattern
        /// </summary>
        public static string DefineSearchPattern = @"#define\s+(?'Name'[\w+]+)(\((?'Argument'[\S]*)\))?\s+(?'Value'(?:[ \t\w\$\#\{_\,\+\*\/\\|=\;\-\.\""\\:\(\)}]*))";

        /// <summary>
        /// The include search pattern
        /// </summary>
        public static string IncludeSearchPattern = @"\#include[ \t]+\""(?'File'[\w+\.]+)\""";

        /// <summary>
        /// The empty line search pattern
        /// </summary>
        public static string EmptyLineSearchPattern = @"^\s+$[\r\n]*";
    }
}
