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

        public AuthViewModel(IAuthClient authBaseAPI, IBaseTokenService baseTokenService, INavigateWindow navigateWindow)
        {
            this.navigateWindow = navigateWindow;
            this.authBaseAPI = authBaseAPI;
            this.baseTokenService = baseTokenService;
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
                navigateWindow.Navigate(new StorePage(navigateWindow, new StoreViewModel()));
            }
            catch (Exception)
            {
            }
        }
    }
}
