using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.Pages;
using SeacClient.Services;
using System;
using System.Threading.Tasks;

namespace SeacClient.ViewModels
{
    public class AuthViewModel
    {
        private readonly INavigateWindow navigateWindow;
        private readonly IAuthClient authBaseAPI;
        private readonly IBaseTokenService baseTokenService;
        private readonly INotificationService notificationService;

        public AuthViewModel(IAuthClient authBaseAPI, IBaseTokenService baseTokenService, INavigateWindow navigateWindow, INotificationService notificationService)
        {
            this.navigateWindow = navigateWindow;
            this.authBaseAPI = authBaseAPI;
            this.baseTokenService = baseTokenService;
            this.notificationService = notificationService;
        }

        public string Login { get; set; }
        public string Password { get; set; }

        public async Task LoginAsync()
        {
            try
            {
                if (string.IsNullOrEmpty(Login) || string.IsNullOrEmpty(Password))
                    return;

                var res = await authBaseAPI.ApiAuthLoginPostAsync(new LoginModel { Login = Login, Password = Password });
                await baseTokenService.SignInAsync(res);
                navigateWindow.Navigate(new StorePage(navigateWindow, new StoreViewModel(await authBaseAPI.ApiUserAsync($"Bearer {res.AccessToken}"), navigateWindow)));
            }
            catch (Exception)
            {
                notificationService.NotifyError("Enter correct login/password");
            }
        }
    }
}
