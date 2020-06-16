using System;

namespace SeacServer.Models
{
    public class ApplicationRelease
    {
        public int Id { get; set; }
        public DateTime DateTime { get; set; }
        public string Version { get; set; }
        public Application Application { get; set; }
    }
}
