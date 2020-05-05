using Microsoft.Extensions.Configuration;
using SeacClient.Pages;
using SeacClient.Settings;
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
        private static IConfigurationRoot configurationRoot;
        private static RuntimeSettings runtimeSettings;
        public static RuntimeSettings RuntimeSettings => runtimeSettings ?? (runtimeSettings = configurationRoot.GetSection("RuntimeSettings").Get<RuntimeSettings>());

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            configurationRoot = new ConfigurationBuilder().AddJsonFile("Properties/appsettings.json").Build();
            RuntimeSettings.PreStartAction();

            navigationWindow = new NavigationWindow
            {
                ShowsNavigationUI = false,
                WindowState = WindowState.Maximized
            };
            navigationWindow.Navigate(new AuthPage());
            navigationWindow.Show();
        }
    }
}
