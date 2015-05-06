using System.Collections.Generic;

namespace ClassForge.Model
{
    public class Class : ClassCollection
    {
        public string Name { get; set; }

        public string Inherits { get; set; }

        public string InternalText { get; set; }

        public Class()
        {
            this.Classes = new List<Class>();
        }
    }
}