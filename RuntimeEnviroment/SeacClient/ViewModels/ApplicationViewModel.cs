using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows.Media;
using ShellLink;
using System.IO;
using SeacClient.Services;
using SeacClient.ViewModels.Applications;

namespace SeacClient.ViewModels
{
    public abstract class ApplicationViewModel
    {
        private readonly Dictionary<SeacRuntime.ExecuteMode, Brush> executeColor = new Dictionary<SeacRuntime.ExecuteMode, Brush>
        {
            { SeacRuntime.ExecuteMode._0, Brushes.White },
            { SeacRuntime.ExecuteMode._1, Brushes.LightBlue },
            { SeacRuntime.ExecuteMode._2, Brushes.LightGreen },
        };
        protected readonly ApplicationModel applicationModel;
        protected readonly ISeacRuntimeClient seacRuntimeClient;

        protected readonly INotificationService notificationService = App.InjectContainer.Resolve<INotificationService>();

        public ApplicationViewModel(ApplicationModel applicationModel, ISeacRuntimeClient seacRuntimeClient)
        {
            this.applicationModel = applicationModel;
            this.seacRuntimeClient = seacRuntimeClient;

            this.MenuContextButtons = new List<MenuContextViewModel>()
            {
                new MenuContextViewModel("Create shortcut", async ()=>await this.CreateShortCut())
            };
        }

        public string Name => applicationModel.Name;
        public string Platform => applicationModel.Platform;
        public string Version => $"({applicationModel.Version})";
        public Brush Color => executeColor[applicationModel.ExecuteMode];
        public Connected_Services.ClientsExtensions.ExecuteMode ExecuteMode => (Connected_Services.ClientsExtensions.ExecuteMode)applicationModel.ExecuteMode;

        public virtual async Task CreateShortCut() => CreateShortCut($"-n {Name} -m {(int)ExecuteMode} -p {Platform}");
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

            notificationService.NotifySuccess("Success create shortcut");
        }

        public virtual List<MenuContextViewModel> MenuContextButtons { get; protected set; }
    }
}
