using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for AuthPage.xaml
    /// </summary>
    public partial class AuthPage : Page
    {
        public AuthPage()
        {
            InitializeComponent();
        }

        private void LoginClick(object sender, RoutedEventArgs e)
            => this.NavigationService.Navigate(new StorePage(new ViewModels.StoreViewModel(new SeacRuntimeClient("https://localhost:5001", new System.Net.Http.HttpClient()))));

        private void RegisterClick(object sender, MouseButtonEventArgs e)
            => this.NavigationService.Navigate(new RegisterPage());
    }
}
