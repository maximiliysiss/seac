using CommonCoreLibrary.APIClient;
using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.ViewModels;
using System.Threading.Tasks;
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
        private readonly MainPage mainPage;
        private readonly AuthViewModel authViewModel;

        public AuthPage(MainPage mainPage)
        {
            this.mainPage = mainPage;
            InitializeComponent();
            this.DataContext = this.authViewModel = new AuthViewModel(App.InjectContainer.Resolve<IAuthClient>(), App.InjectContainer.Resolve<IBaseTokenService>(), mainPage);
        }

        private void LoginClick(object sender, RoutedEventArgs e)
        {
            authViewModel.Password = PasswordBox.Password;
            authViewModel.LoginAsync();
        }

        private void RegisterClick(object sender, MouseButtonEventArgs e) => this.mainPage.Navigate(new RegisterPage(mainPage));
    }
}
