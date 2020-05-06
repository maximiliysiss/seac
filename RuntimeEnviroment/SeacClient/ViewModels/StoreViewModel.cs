using SeacClient.Pages;
using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Documents;

namespace SeacClient.ViewModels
{
    public class StoreViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop = null) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        public Page Source { get; private set; }
        public List<MenuButtonViewModel> MenuButtons { get; private set; }

        public StoreViewModel()
        {
            this.MenuButtons = new List<MenuButtonViewModel>
            {
                new MenuButtonViewModel("STORE", "store", this),
                new MenuButtonViewModel("LIBRARY", "library", this),
                new MenuButtonViewModel("SETTINGS", "settings", this),
            };
        }

        public void NavigateTo(string uri)
        {
            this.MenuButtons.ForEach(x => x.IsSelected = false);
            var resBtn = this.MenuButtons.FirstOrDefault(x => x.Uri == uri);
            if (resBtn != null)
                resBtn.IsSelected = true;

            switch (uri)
            {
                case "store":
                    Source = new ApplicationListPage(new ApplicationsListViewModel(App.InjectContainer.Resolve<ISeacRuntimeClient>(), "Store"));
                    break;
                case "library":
                    Source = new ApplicationListPage(new ApplicationsListViewModel(App.InjectContainer.Resolve<ISeacRuntimeClient>(), "Library"));
                    break;
                case "settings":
                    Source = new SettingsPage();
                    break;
                case "usersettings":
                    Source = new UserSettingsPage();
                    break;
            }

            OnPropertyChanged("Source");
        }

        public async Task Load() => NavigateTo("store");
    }
}
