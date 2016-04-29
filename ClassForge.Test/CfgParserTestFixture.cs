using System;
using System.Collections.Generic;
using System.Diagnostics;
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

        [Test]
        public void DirectoryTest()
        {
            var parser = new CfgSimpleParser();
            var watch = Stopwatch.StartNew();
            var models = parser.ParseDirectory("files\\mergetest");
            watch.Stop();
            Console.WriteLine(watch.ElapsedMilliseconds);
        }

        [Test]
        public void DirectoryMergeTest()
        {
            var parser = new CfgSimpleParser();
            var watch = Stopwatch.StartNew();
            var model = parser.ParseDirectoryMerged("files\\mergetest");
            model.UpdateReferences();
            watch.Stop();
            DrawModel(model);
            Console.WriteLine(watch.ElapsedMilliseconds);
        }

        [Test]
        public void DirectoryDerefTest()
        {
            var parser = new CfgSimpleParser();
            var watch = Stopwatch.StartNew();
            var model = parser.ParseDirectoryMerged("files\\mergetest");
            model.UpdateReferences();
            watch.Stop();
            DrawModel(model);

            var dm = parser.GetDereferencedModel(model);
            Console.WriteLine(dm.ToJson());

            Console.WriteLine(watch.ElapsedMilliseconds);
        }

        private void DrawModel(Model.Model model)
        {
            var level = 0;

            var sb = new StringBuilder();

            foreach (var w in model.Classes)
            {
                DrawClass(w, level, ref sb);
            }

            Console.WriteLine(sb.ToString());
        }

        private void DrawClass(Class c, int level, ref StringBuilder sb)
        {
            string sepString = string.Empty;

            for (int i = 0; i < level; i++)
            {
                sepString += ". ";
            }

            sepString += string.Format("+- {0}", c.Name);

            if(c.InheritanceClass != null)
                sepString += string.Format(" : {0}", c.InheritanceClass.Name);

            //if(c.ContainmentParent != null)
               // sepString += string.Format(" in {0}", c.ContainmentParent.Name);

            sb.AppendLine(sepString);

            foreach (var w in c.Classes)
            {
                this.DrawClass(w, level + 1, ref sb);
            }
        }
    }
}
