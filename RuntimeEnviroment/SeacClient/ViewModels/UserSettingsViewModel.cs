using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.Pages;
using SeacClient.Services;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace SeacClient.ViewModels
{
    public class UserSettingsViewModel
    {
        private readonly INavigateWindow navigateWindow;
        private readonly IBaseTokenService baseTokenService;

        public UserSettingsViewModel(INavigateWindow navigateWindow, IBaseTokenService baseTokenService)
        {
            this.navigateWindow = navigateWindow;
            this.baseTokenService = baseTokenService;
        }

        public async Task Logout()
        {
            await baseTokenService.SignOutAsync();
            navigateWindow.Navigate(new AuthPage(navigateWindow, new AuthViewModel(App.InjectContainer.Resolve<IAuthClient>(), App.InjectContainer.Resolve<IBaseTokenService>(), navigateWindow,
                App.InjectContainer.Resolve<INotificationService>())));
        }
    }
}
