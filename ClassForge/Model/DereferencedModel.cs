namespace ClassForge.Model
{
    using System.Collections.Generic;
    using Newtonsoft.Json;
    using Newtonsoft.Json.Serialization;

    /// <summary>
    /// Provides the description for fully dereferenced model
    /// </summary>
    public class DereferencedModel
    {
        /// <summary>
        /// Gets or sets the list of <see cref="Class"/>
        /// </summary>
        public List<Class> Classes { get; set; }
        
        /// <summary>
        /// Gets or sets the list of <see cref="Property"/>
        /// </summary>
        public List<Property> Properties { get; set; }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="model">Needs a model to dereference.</param>
        public DereferencedModel(Model model)
        {
            this.Classes = new List<Class>();
            this.Properties = new List<Property>();

            foreach(var aclass in model.Classes)
            {
                this.DereferenceClass(aclass);
            }
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        public DereferencedModel()
        {
            this.Classes = new List<Class>();
            this.Properties = new List<Property>();
        }

        /// <summary>
        /// Dereferences a class.
        /// </summary>
        /// <param name="cl">The class to dereference.</param>
        private void DereferenceClass(Class cl)
        {
            if (cl == null) return;

            if(this.Classes.Contains(cl)) return;

            this.Classes.Add(cl);
            this.Properties.AddRange(cl.Properties);
            
            this.DereferenceClass(cl.InheritanceClass);
            //this.DereferenceClass(cl.ContainmentParent);

            foreach(var cf in cl.Classes)
            {
                this.DereferenceClass(cf);
            }
        }

        /// <summary>
        /// Converts this object to Json
        /// </summary>
        /// <returns>Formatted json string.</returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented, new JsonSerializerSettings() {ContractResolver = new CamelCasePropertyNamesContractResolver()});
        }
    }
}
