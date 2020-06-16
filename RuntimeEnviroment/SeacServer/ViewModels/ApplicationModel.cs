using SeacServer.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SeacServer.ViewModels
{
    public class ApplicationModel
    {
        public string Name { get; set; }
        public string Version { get; set; }
        public string Platform { get; set; }
        public ExecuteMode ExecuteMode { get; set; }
    }
}
