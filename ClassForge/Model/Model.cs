using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassForge.Model
{
    public class Model : ClassCollection
    {
        public Model()
        {
            this.Classes = new List<Class>();
        }
    }
}
