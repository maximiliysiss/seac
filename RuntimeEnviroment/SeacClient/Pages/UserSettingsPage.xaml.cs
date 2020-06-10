using SeacClient.ViewModels;
using System.Windows;
using System.Windows.Controls;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for UserSettingsPage.xaml
    /// </summary>
    public partial class UserSettingsPage : Page
    {
        private readonly UserSettingsViewModel userSettingsViewModel;

        public UserSettingsPage(UserSettingsViewModel userSettingsViewModel)
        {
            this.Uid = nameof(UserSettingsPage);
            InitializeComponent();
            this.DataContext = this.userSettingsViewModel = userSettingsViewModel;
        }

        private async void LogoutClick(object sender, RoutedEventArgs e)
        {
            await userSettingsViewModel.Logout();
        }
    }
}
