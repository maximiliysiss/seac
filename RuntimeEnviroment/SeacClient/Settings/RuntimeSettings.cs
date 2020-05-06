using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SeacClient.Settings
{
    public class RuntimeSettings
    {
        public string Repo { get; set; }
        public string CLR { get; set; }
        public string ServerURL { get; set; }

        public void PreStartAction()
        {
            if (!Directory.Exists(Repo))
                Directory.CreateDirectory(Repo);
        }
    }
}
