using SeacClient.SeacRuntime;
using System.Threading.Tasks;
using SeacClient.Connected_Services.ClientsExtensions;
using System.Windows;
using System.Diagnostics;
using System.IO;

namespace SeacClient.ViewModels.Applications
{
    public class SingleApplication : ApplicationViewModel
    {
        private readonly string directory;
        private readonly string file;

        public SingleApplication(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient) : base(applicationModel, seacRuntimeClient)
        {
            directory = $"{App.RuntimeSettings.Repo}{Name}_{Platform}_{ExecuteMode.ToString().ToLower()}";
            file = $"{directory}\\{Name}.seac";

            MenuContextButtons.Add(new MenuContextViewModel("Update", async () => await Update()));
            MenuContextButtons.Add(new MenuContextViewModel("Delete", async () => await Delete()));
        }

        private async Task Delete()
        {
            if (!File.Exists(file))
                throw new FileNotFoundException(file);

            File.Delete(file);

            notificationService.NotifySuccess("Success delete application");
        }

        private async Task Update()
        {
            if (!File.Exists(file))
                throw new FileNotFoundException(file);

            File.Delete(file);
            await DownloadFile();

            notificationService.NotifySuccess("Success update application");
        }

        private async Task DownloadFile()
        {
            var res = await seacRuntimeClient.CallStream(seacRuntimeClient.ApiRuntimeAsync(Name, Platform, ExecuteMode.ToString().ToLower()));
            Directory.CreateDirectory(directory);
            File.Create(file).Close();
            File.WriteAllBytes(file, res);
        }

        public override async Task CreateShortCut() => CreateShortCut($"-n {Name} -m {(int)ExecuteMode} -p {Platform} -f \"{file}\"");

        public override async Task OnClickAsync()
        {
            if (!File.Exists(file))
            {
                var dialogResult = MessageBox.Show("Download application?", "Download", MessageBoxButton.YesNo);
                if (dialogResult != MessageBoxResult.Yes)
                    return;
                await DownloadFile();
            }

            Process process = new Process
            {
                StartInfo = new ProcessStartInfo(App.RuntimeSettings.CLR, $"-n {Name} -m {(int)ExecuteMode} -p {Platform} -f \"{file}\"")
                {
                    WorkingDirectory = Directory.GetParent(App.RuntimeSettings.CLR).ToString()
                }
            };
            process.Start();
        }
    }
}
