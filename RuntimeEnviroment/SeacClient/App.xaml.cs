using SeacClient.Pages;
using System.Windows;
using System.Windows.Navigation;

namespace SeacClient
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private NavigationWindow navigationWindow;

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            navigationWindow = new NavigationWindow();
            navigationWindow.ShowsNavigationUI = false;
            navigationWindow.WindowState = WindowState.Maximized;
            navigationWindow.Navigate(new AuthPage());
            navigationWindow.Show();
        }
    }
}
