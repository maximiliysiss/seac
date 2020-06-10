using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.SeacRuntime;
using SeacClient.Services;
using SeacClient.ViewModels;
using System.Windows;
using System.Windows.Controls;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for RegisterPage.xaml
    /// </summary>
    public partial class RegisterPage : Page
    {
        private readonly INavigateWindow mainPage;
        private readonly RegisterViewModel registerViewModel;

        public RegisterPage(INavigateWindow mainPage, RegisterViewModel registerViewModel)
        {
            this.Uid = nameof(RegisterPage);
            this.mainPage = mainPage;
            InitializeComponent();
            this.DataContext = this.registerViewModel = registerViewModel;
        }

        private async void RegisterClick(object sender, RoutedEventArgs e)
        {
            registerViewModel.ConfirmPassword = ConfirmedPassword.Password.Trim();
            registerViewModel.Password = Password.Password.Trim();
            await registerViewModel.RegisterAsync();
        }
        private void ReturnToAuth(object sender, System.Windows.Input.MouseButtonEventArgs e) => mainPage.GoBack();
    }
}
