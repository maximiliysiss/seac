using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.Pages;
using SeacClient.SeacRuntime;
using SeacClient.Services;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace SeacClient.ViewModels
{
    public class StoreViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop = null) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        public Page Source { get; private set; }
        public List<MenuButtonViewModel> MenuButtons { get; private set; }

        public StoreViewModel(UserModel userModel, INavigateWindow navigateWindow)
        {
            this.MenuButtons = new List<MenuButtonViewModel>
            {
                new MenuButtonViewModel("STORE", "store", this),
                new MenuButtonViewModel("LIBRARY", "library", this),
                new MenuButtonViewModel("SETTINGS", "settings", this),
                new MenuButtonViewModel("DEVELOPMENT", "develop", this),
            };

            this.UserModel = userModel;
            this.navigateWindow = navigateWindow;
        }

        public UserModel UserModel { get; private set; }

        private readonly INavigateWindow navigateWindow;

        public void NavigateTo(string uri)
        {
            this.MenuButtons.ForEach(x => x.IsSelected = false);
            var resBtn = this.MenuButtons.FirstOrDefault(x => x.Uri == uri);
            if (resBtn != null)
                resBtn.IsSelected = true;

            switch (uri)
            {
                case "store":
                    Source = new ApplicationListPage(new ApplicationsListViewModel(App.InjectContainer.Resolve<ISeacRuntimeClient>(), "Store", System.Windows.Visibility.Collapsed));
                    break;
                case "library":
                    Source = new ApplicationListPage(new ApplicationsListViewModel(App.InjectContainer.Resolve<ISeacRuntimeClient>(), "Library", System.Windows.Visibility.Visible));
                    break;
                case "settings":
                    Source = new SettingsPage();
                    break;
                case "usersettings":
                    Source = new UserSettingsPage(new UserSettingsViewModel(navigateWindow, App.InjectContainer.Resolve<IBaseTokenService>()));
                    break;
                case "report":
                    Source = new ReportPage();
                    break;
                case "develop":
                    Source = new DevelopmentPage();
                    break;
            }

            OnPropertyChanged("Source");
        }

        public async Task Load() => NavigateTo("store");
    }
}
