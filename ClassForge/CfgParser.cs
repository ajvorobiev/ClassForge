// --------------------------------------------------------------------------------------------------------------------
// <copyright file="CfgParser.cs" company="RHS">
//   Copyright Red Hammer Studios
// </copyright>
// <summary>
//   Defines the file CfgParser type.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace ClassForge
{
    using System.IO;

    /// <summary>
    /// The this.parser takes care of loading in the structure of the config
    /// </summary>
    public class CfgParser
    {
        /// <summary>
        /// The engine instantiation
        /// </summary>
        private readonly GOLD.Parser parser = new GOLD.Parser();

        /// <summary>
        /// The top of the tree
        /// </summary>
        private GOLD.Reduction root;

        /// <summary>
        /// Initializes a new instance of the <see cref="CfgParser"/> class.
        /// </summary>
        /// <param name="filePath">
        /// The path of the file to be parsed.
        /// </param>
        public CfgParser(string filePath)
        {
            if (this.Setup("cfggrammar\\armaconfig.egt"))
            {
                // start constructing parsing
                this.Parse(new StringReader(File.ReadAllText(filePath)));

            } 
            else
            {
                this.FailMessage = "Grammar failed to load.";
            }
        }

        /// <summary>
        /// The parse method.
        /// </summary>
        /// <param name="stringReader">
        /// The string reader.
        /// </param>
        /// <returns>
        /// The <see cref="bool"/>.
        /// </returns>
        private bool Parse(TextReader stringReader)
        {
            // This procedure starts the GOLD this.parser Engine and handles each of the
            // messages it returns. Each time a reduction is made, you can create new
            // custom object and reassign the .CurrentReduction property. Otherwise, 
            // the system will use the Reduction object that was returned.
            // 
            // The resulting tree will be a pure representation of the language 
            // and will be ready to implement.
            GOLD.ParseMessage response;

            bool accepted = false;          // Was the parse successful?

            this.parser.Open(stringReader);
            this.parser.TrimReductions = false;  // Please read about this feature before enabling  

            var done = false;

            // perfomr the parsing
            while (!done)
            {
                response = this.parser.Parse();

                switch (response)
                {
                    case GOLD.ParseMessage.LexicalError:
                        // Cannot recognize token
                        this.FailMessage = "Lexical Error:\n" +
                                      "Position: " + this.parser.CurrentPosition().Line + ", " + this.parser.CurrentPosition().Column + "\n" +
                                      "Read: " + this.parser.CurrentToken().Data;
                        done = true;
                        break;

                    case GOLD.ParseMessage.SyntaxError:
                        // Expecting a different token
                        this.FailMessage = "Syntax Error:\n" +
                                      "Position: " + this.parser.CurrentPosition().Line + ", " + this.parser.CurrentPosition().Column + "\n" +
                                      "Read: " + this.parser.CurrentToken().Data + "\n" +
                                      "Expecting: " + this.parser.ExpectedSymbols().Text();
                        done = true;
                        break;

                    case GOLD.ParseMessage.Reduction:
                        // For this project, we will let the this.parser build a tree of Reduction objects
                        // this.parser.CurrentReduction = CreateNewObject(parser.CurrentReduction);
                        break;

                    case GOLD.ParseMessage.Accept:
                        // Accepted!
                        this.root = (GOLD.Reduction)this.parser.CurrentReduction;    // The root node!                                  
                        done = true;
                        accepted = true;
                        break;

                    case GOLD.ParseMessage.TokenRead:
                        // You don't have to do anything here.
                        break;

                    case GOLD.ParseMessage.InternalError:
                        // INTERNAL ERROR! Something is horribly wrong.
                        done = true;
                        break;

                    case GOLD.ParseMessage.NotLoadedError:
                        // This error occurs if the CGT was not loaded.                   
                        this.FailMessage = "Tables not loaded";
                        done = true;
                        break;

                    case GOLD.ParseMessage.GroupError:
                        // GROUP ERROR! Unexpected end of file
                        this.FailMessage = "Runaway group";
                        done = true;
                        break;
                }
            } // while

            return accepted;
        }

        /// <summary>
        /// Gets or sets the error message
        /// </summary>
        public string FailMessage { get; set; }

        /// <summary>
        /// The setup.
        /// </summary>
        /// <param name="filePath">
        /// The file path.
        /// </param>
        /// <returns>
        /// The <see cref="bool"/>.
        /// </returns>
        public bool Setup(string filePath)
        {
            return this.parser.LoadTables(filePath);
        }
    }
}
