using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows.Media;
using SeacClient.Connected_Services.ClientsExtensions;
using System.Windows;
using System.Diagnostics;
using ShellLink;
using System.IO;

namespace SeacClient.ViewModels
{
    public abstract class ApplicationViewModel
    {
        private readonly Dictionary<SeacRuntime.ExecuteMode, Brush> executeColor = new Dictionary<SeacRuntime.ExecuteMode, Brush>
        {
            { SeacRuntime.ExecuteMode._0, Brushes.Black },
            { SeacRuntime.ExecuteMode._1, Brushes.Blue },
            { SeacRuntime.ExecuteMode._2, Brushes.Green },
        };
        protected readonly ApplicationModel applicationModel;
        protected readonly ISeacRuntimeClient seacRuntimeClient;

        public ApplicationViewModel(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient)
        {
            this.applicationModel = applicationModel;
            this.seacRuntimeClient = seacRuntimeClient;
        }

        public string Name => applicationModel.Name;
        public string Platform => applicationModel.Platform;
        public string Version => $"({applicationModel.Version})";
        public Brush Color => executeColor[applicationModel.ExecuteMode];
        public Connected_Services.ClientsExtensions.ExecuteMode ExecuteMode => (Connected_Services.ClientsExtensions.ExecuteMode)applicationModel.ExecuteMode;

        public async Task CreateShortCut() => CreateShortCut($"-n {Name} -m {(int)ExecuteMode} -p {Platform}");
        public abstract Task OnClickAsync();

        public static ApplicationViewModel CreateViewModel(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient)
        {
            return ((Connected_Services.ClientsExtensions.ExecuteMode)applicationModel.ExecuteMode) switch
            {
                Connected_Services.ClientsExtensions.ExecuteMode.Single => new SingleApplication(applicationModel, seacRuntimeClient),
                Connected_Services.ClientsExtensions.ExecuteMode.Remote => new RemoteApplication(applicationModel, seacRuntimeClient),
                Connected_Services.ClientsExtensions.ExecuteMode.FullRemote => new FullRemoteApplication(applicationModel, seacRuntimeClient),
                _ => null,
            };
        }

        protected void CreateShortCut(string cmd)
        {
            var desktopDir = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            var lnk = Shortcut.CreateShortcut($"{App.RuntimeSettings.CLR}", cmd, Directory.GetParent(App.RuntimeSettings.CLR).ToString());
            lnk.WriteToFile($"{desktopDir}/{Name}.lnk");
        }
    }

    public class SingleApplication : ApplicationViewModel
    {
        public SingleApplication(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient) : base(applicationModel, seacRuntimeClient)
        {
        }

        public override async Task OnClickAsync()
        {
            var directory = $"{App.RuntimeSettings.Repo}{Name}_{Platform}_{ExecuteMode.ToString().ToLower()}";
            var file = $"{directory}\\{Name}.seac";
            if (!File.Exists(file))
            {
                var dialogResult = MessageBox.Show("Download application?", "Download", MessageBoxButton.YesNo);
                if (dialogResult != MessageBoxResult.Yes)
                    return;
                var res = await seacRuntimeClient.CallStream(seacRuntimeClient.ApiRuntimeAsync(Name, Platform, ExecuteMode.ToString().ToLower()));
                Directory.CreateDirectory(directory);
                File.Create(file).Close();
                File.WriteAllBytes(file, res);
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

    public class RemoteApplication : ApplicationViewModel
    {
        public RemoteApplication(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient) : base(applicationModel, seacRuntimeClient)
        {
        }

        public async override Task OnClickAsync()
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


    public class FullRemoteApplication : ApplicationViewModel
    {
        public FullRemoteApplication(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient) : base(applicationModel, seacRuntimeClient)
        {
        }

        public override Task OnClickAsync()
        {
            throw new NotImplementedException();
        }
    }
}
