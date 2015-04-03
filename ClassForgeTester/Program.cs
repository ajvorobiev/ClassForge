using System;
using System.Text;
using ClassForge;

namespace ClassForgeTester
{
    /// <summary>
    /// Main entry point
    /// </summary>
    class Program
    {
        /// <summary>
        /// The main.
        /// </summary>
        /// <param name="args">
        /// The arguments.
        /// </param>
        static void Main(string[] args)
        {
            var parser = new CfgParser("files\\config.cpp");

            DrawReductionTree(parser.Root);

            Console.WriteLine(parser.FailMessage);
            Console.ReadKey();
        }

        private static void DrawReductionTree(GOLD.Reduction Root)
        {
            //This procedure starts the recursion that draws the parse tree.
            StringBuilder tree = new StringBuilder();

            tree.AppendLine("+-" + Root.Parent.Text(false));
            DrawReduction(tree, Root, 1);

            Console.WriteLine(tree.ToString());
        }

        private static void DrawReduction(StringBuilder tree, GOLD.Reduction reduction, int indent)
        {
            //This is a simple recursive procedure that draws an ASCII version of the parse
            //tree

            int n;
            string indentText = "";

            for (n = 1; n <= indent; n++)
            {
                indentText += "| ";
            }

            //=== Display the children of the reduction
            for (n = 0; n < reduction.Count(); n++)
            {
                switch (reduction[n].Type())
                {
                    case GOLD.SymbolType.Nonterminal:
                        GOLD.Reduction branch = (GOLD.Reduction)reduction[n].Data;

                        tree.AppendLine(indentText + "+-" + branch.Parent.Text(false));
                        DrawReduction(tree, branch, indent + 1);
                        break;

                    default:
                        string leaf = (string)reduction[n].Data;

                        tree.AppendLine(indentText + "+-" + leaf);
                        break;
                }
            }
        }
    }
}
