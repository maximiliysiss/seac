using Microsoft.Extensions.Configuration;
using SeacClient.Pages;
using SeacClient.SeacRuntime;
using SeacClient.Services;
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
        private static IInjectContainer injectContainer;
        public static IInjectContainer InjectContainer => injectContainer;
        public static RuntimeSettings RuntimeSettings => runtimeSettings ?? (runtimeSettings = configurationRoot.GetSection("RuntimeSettings").Get<RuntimeSettings>());

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            configurationRoot = new ConfigurationBuilder().AddJsonFile("Properties/appsettings.json").Build();
            RuntimeSettings.PreStartAction();
            injectContainer = new ApplicationContainer();
            injectContainer.Bind<ISeacRuntimeClient, SeacRuntimeClient>(new System.Collections.Generic.Dictionary<string, object>
            {
                { "baseUrl", RuntimeSettings.ServerURL},
                { "httpClient",new System.Net.Http.HttpClient()  }
            });

            navigationWindow = new NavigationWindow
            {
                ShowsNavigationUI = false,
                WindowState = WindowState.Maximized
            };
            navigationWindow.Title = "Seac Runtime";
            navigationWindow.Navigate(new AuthPage());
            navigationWindow.Show();
        }
    }
}
