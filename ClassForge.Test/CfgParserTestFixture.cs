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
            parser.Parse("files\\config.cpp");
        }
    }
}
