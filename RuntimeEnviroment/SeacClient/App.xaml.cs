using CommonCoreLibrary.Auth.Interfaces;
using Microsoft.Extensions.Configuration;
using SeacClient.AuthAPI;
using SeacClient.Pages;
using SeacClient.Services;
using SeacClient.Settings;
using SeacClient.ViewModels;
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
        public static IInjectContainer InjectContainer => injectContainer ?? (injectContainer = new ApplicationContainer());
        public static RuntimeSettings RuntimeSettings => runtimeSettings ?? (runtimeSettings = configurationRoot.GetSection("RuntimeSettings").Get<RuntimeSettings>());

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            configurationRoot = new ConfigurationBuilder().AddJsonFile("Properties/appsettings.json").Build();
            RuntimeSettings.PreStartAction();
            InjectContainer.Init(configurationRoot, RuntimeSettings);

            navigationWindow = new NavigationWindow
            {
                ShowsNavigationUI = false,
                ResizeMode = ResizeMode.NoResize,
                WindowState = WindowState.Normal,
                WindowStyle = WindowStyle.None
            };
            navigationWindow.Title = "Seac Runtime";
            var viewModel = new ViewModels.MainPageViewModel();
            MainPage mainPage = new MainPage(viewModel);
            viewModel.Source = new AuthPage(mainPage, new AuthViewModel(InjectContainer.Resolve<IAuthClient>(), InjectContainer.Resolve<IBaseTokenService>(), mainPage,
                InjectContainer.Resolve<INotificationService>()));
            navigationWindow.Navigate(mainPage);
            navigationWindow.Show();
        }
    }
}
