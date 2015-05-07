using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClassForge.Model;
using NUnit.Framework;

namespace ClassForge.Test
{
    [TestFixture]
    public class CfgParserTestFixture
    {
        [SetUp]
        public void SetUp()
        {
            
        }

        [TearDown]
        public void TearDown()
        {
            
        }

        [Test]
        public void TextParserTest()
        {
            var parser = new CfgSimpleParser();
            parser.Parse("files\\config2.cpp");

            var indent = 1;

            foreach (var cl in parser.Model.Classes)
            {
                Console.WriteLine(cl.StringOutput(indent));
                this.DrawClass(cl, indent + 1);
            }
        }

        private void DrawClass(Class cl, int indent)
        {
            foreach (var cla in cl.Classes)
            {
                Console.WriteLine(cla.StringOutput(indent));
                this.DrawClass(cla, indent + 1);
            }
        }
    }
}
