using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.Services;
using SeacClient.ViewModels;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for AuthPage.xaml
    /// </summary>
    public partial class AuthPage : Page
    {
        private readonly INavigateWindow mainPage;
        private readonly AuthViewModel authViewModel;

        public AuthPage(INavigateWindow mainPage, AuthViewModel authViewModel)
        {
            this.Uid = nameof(AuthPage);
            this.mainPage = mainPage;
            InitializeComponent();
            this.DataContext = this.authViewModel = authViewModel;
        }

        private void LoginClick(object sender, RoutedEventArgs e)
        {
            authViewModel.Password = PasswordBox.Password;
            authViewModel.LoginAsync();
        }

        private void RegisterClick(object sender, MouseButtonEventArgs e) => this.mainPage.Navigate(new RegisterPage(mainPage,
            new RegisterViewModel(App.InjectContainer.Resolve<IAuthClient>(), App.InjectContainer.Resolve<IBaseTokenService>(), mainPage, App.InjectContainer.Resolve<INotificationService>())));
    }
}
