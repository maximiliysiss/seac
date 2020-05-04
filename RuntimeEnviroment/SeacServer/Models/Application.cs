using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SeacServer.Models
{
    public enum ExecuteMode
    {
        Single,
        Remote,
        FullRemote
    }

    public class Application
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Version { get; set; }
        public string Platform { get; set; }
        public ExecuteMode ExecuteMode { get; set; }
    }
}
