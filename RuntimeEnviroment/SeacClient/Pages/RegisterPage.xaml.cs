using SeacClient.SeacRuntime;
using System.Windows;
using System.Windows.Controls;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for RegisterPage.xaml
    /// </summary>
    public partial class RegisterPage : Page
    {
        public RegisterPage()
        {
            InitializeComponent();
        }

        private void RegisterClick(object sender, RoutedEventArgs e) => this.NavigationService.Navigate(new StorePage(new ViewModels.StoreViewModel()));
    }
}
