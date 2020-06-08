using SeacClient.SeacRuntime;
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
        private readonly MainPage mainPage;

        public RegisterPage(MainPage mainPage)
        {
            this.mainPage = mainPage;
            InitializeComponent();
            this.DataContext = new RegisterViewModel();
        }

        private void RegisterClick(object sender, RoutedEventArgs e) => this.mainPage.Navigate(new StorePage(mainPage, new ViewModels.StoreViewModel()));
        private void ReturnToAuth(object sender, System.Windows.Input.MouseButtonEventArgs e) => mainPage.Navigate(new AuthPage(mainPage));
    }
}
