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

        public AuthPage(MainPage mainPage)
        {
            this.mainPage = mainPage;
            InitializeComponent();
        }

        private void LoginClick(object sender, RoutedEventArgs e) => this.mainPage.Navigate(new StorePage(mainPage, new ViewModels.StoreViewModel()));
        private void RegisterClick(object sender, MouseButtonEventArgs e) => this.mainPage.Navigate(new RegisterPage(mainPage));
    }
}
