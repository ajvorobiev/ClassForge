// --------------------------------------------------------------------------------------------------------------------
// <copyright file="Class.cs" company="Red Hammer Studios">
//   Copyright (c) 2015 Red Hammer Studios
// </copyright>
// <summary>
//   The class.
// nuget pack ClassForge.csproj -Prop Configuration=Release;Platform=AnyCPU
// nuget.exe push ClassForge.dll.1.6.0.nupkg
// </summary>
// --------------------------------------------------------------------------------------------------------------------

using System;

namespace ClassForge.Model
{
    using System.Collections.Generic;
    using Newtonsoft.Json;

    /// <summary>
    /// The class.
    /// </summary>
    public class Class : ClassCollection
    {
        /// <summary>
        /// Gets or sets the unique id.
        /// </summary>
        public Guid Iid { get; set; }

        /// <summary>
        /// The class map.
        /// </summary>
        [JsonIgnore]
        private Dictionary<string, Class> ClassMap;

        /// <summary>
        /// Gets or sets the name of the parent class.
        /// </summary>
        public string Inherits { get; set; }

        /// <summary>
        /// Gets or sets the containment parent.
        /// </summary>
        [JsonIgnore]
        public Class ContainmentParent { get; set; }

        /// <summary>
        /// Gets or sets the containment parent iid.
        /// </summary>
        public Guid ContainmentParentIid {
            get
            {
                if (this.ContainmentParent == null) { return Guid.Empty;}
                return this.ContainmentParent.Iid;
            }
        }

        /// <summary>
        /// Gets or sets the inheritance class.
        /// </summary>
        [JsonIgnore]
        public Class InheritanceClass { get; set; }

        /// <summary>
        /// Gets or sets the inheritance class iid.
        /// </summary>
        public Guid InheritanceClassIid {
            get
            {
                if (this.InheritanceClass == null) { return Guid.Empty; }
                return this.InheritanceClass.Iid;
            } }

        /// <summary>
        /// Gets or sets the inheritance children.
        /// </summary>
        [JsonIgnore]
        public List<Class> InheritanceChildren { get; set; } 

        /// <summary>
        /// Gets or sets the remark
        /// </summary>
        public string Remark { get; set; }

        /// <summary>
        /// Gets or sets the list of <see cref="Property"/>'s
        /// </summary>
        [JsonIgnore]
        public List<Property> Properties { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="Class"/> class.
        /// </summary>
        public Class()
        {
            this.Iid = Guid.NewGuid();
            this.Classes = new List<Class>();
            this.Properties = new List<Property>();
            this.InheritanceChildren = new List<Class>();
        }

        /// <summary>
        /// Updates the model references
        /// </summary>
        public void UpdateReferences(Class parent)
        {
            this.ClassMap = new Dictionary<string, Class>();

            this.ContainmentParent = parent;
            
            foreach (var cl in this.Classes)
            {
                try
                {
                    this.ClassMap.Add(cl.Name.ToLower(), cl);
                }
                catch (Exception ex)
                {
                    //Console.WriteLine("The class named {0} already exists in classmap", cd.Name);
                }
            }

            foreach (var cl in this.Classes)
            {
                this.UpdateClassReference(cl, this);
            }
        }

        /// <summary>
        /// Updates the class references.
        /// </summary>
        /// <param name="cl">
        /// The child class.
        /// </param>
        /// <param name="parent">
        /// The parent class.
        /// </param>
        private void UpdateClassReference(Class cl, Class parent)
        {
            cl.ContainmentParent = parent;
            Class inheritanceClass;

            if (this.ClassMap.TryGetValue(cl.Inherits.ToLower(), out inheritanceClass))
            {
                if (cl != inheritanceClass)
                {
                    cl.InheritanceClass = inheritanceClass;
                    if (!inheritanceClass.InheritanceChildren.Contains(cl))
                    {
                        inheritanceClass.InheritanceChildren.Add(cl);
                    } 
                }
            }

            foreach (var cd in cl.Classes)
            {
                cd.UpdateReferences(cl);
            }
        }
    }
}