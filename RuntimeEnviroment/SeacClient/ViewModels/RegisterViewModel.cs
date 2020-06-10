using CommonCoreLibrary.Auth.Interfaces;
using SeacClient.AuthAPI;
using SeacClient.Pages;
using SeacClient.Services;
using System;
using System.Threading.Tasks;

namespace SeacClient.ViewModels
{
    public class RegisterViewModel
    {
        private readonly INavigateWindow navigateWindow;
        private readonly IAuthClient authBaseAPI;
        private readonly IBaseTokenService baseTokenService;
        private readonly INotificationService notificationService;

        public RegisterViewModel(IAuthClient authBaseAPI, IBaseTokenService baseTokenService, INavigateWindow navigateWindow, INotificationService notificationService)
        {
            this.navigateWindow = navigateWindow;
            this.authBaseAPI = authBaseAPI;
            this.baseTokenService = baseTokenService;
            this.notificationService = notificationService;
        }

        public string Login { get; set; }
        public string Password { get; set; }
        public string ConfirmPassword { get; set; }

        public async Task RegisterAsync()
        {
            try
            {
                if (string.IsNullOrEmpty(Login) || string.IsNullOrEmpty(Password) || string.IsNullOrEmpty(ConfirmPassword) || ConfirmPassword != Password)
                    return;

                var res = await authBaseAPI.ApiAuthRegisterAsync(new RegisterModel { Email = Login, Nickname = Login, Password = Password });
                await baseTokenService.SignInAsync(res);
                navigateWindow.Navigate(new StorePage(navigateWindow, new StoreViewModel(await authBaseAPI.ApiUserAsync($"Bearer {res.AccessToken}"), navigateWindow)));
            }
            catch (Exception)
            {
                notificationService.NotifyError("Register error");
            }
        }
    }
}
