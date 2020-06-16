using SeacClient.SeacRuntime;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace SeacClient.ViewModels.Applications
{
    public class FullRemoteApplication : ApplicationViewModel
    {
        public FullRemoteApplication(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient) : base(applicationModel, seacRuntimeClient)
        {
        }

        public override async Task OnClickAsync()
        {
            Process process = new Process
            {
                StartInfo = new ProcessStartInfo(App.RuntimeSettings.CLR, $"-n {Name} -m {(int)ExecuteMode} -p {Platform}")
                {
                    WorkingDirectory = Directory.GetParent(App.RuntimeSettings.CLR).ToString()
                }
            };
            process.Start();
        }
    }
}
