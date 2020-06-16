using SeacClient.SeacRuntime;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;

namespace SeacClient.ViewModels.Applications
{
    public class LocalApplication : ApplicationViewModel
    {
        public LocalApplication(ApplicationModel applicationModel) : base(applicationModel, null)
        {
        }

        public override Task OnClickAsync()
        {
            if (!File.Exists(applicationModel.Name))
                return Task.CompletedTask;

            Process process = new Process
            {
                StartInfo = new ProcessStartInfo(App.RuntimeSettings.CLR, $"-n {Path.GetFileNameWithoutExtension(Name)} -m {(int)ExecuteMode} -p Windows -f \"{applicationModel.Name}\"")
                {
                    WorkingDirectory = Directory.GetParent(App.RuntimeSettings.CLR).ToString()
                }
            };
            process.Start();
            return Task.CompletedTask;
        }
    }
}
