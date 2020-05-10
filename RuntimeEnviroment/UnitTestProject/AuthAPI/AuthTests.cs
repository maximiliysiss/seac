using AuthAPI.Models.Controller;
using AuthAPI.Models.Database;
using AuthAPI.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;

namespace UnitTestProject.AuthAPI
{
    [TestClass]
    public class AuthTests
    {
        private readonly IAuthService authService;

        public AuthTests()
        {
            var tokenMock = new Mock<ITokenService>();
            tokenMock.Setup(x => x.GenerateToken(It.IsAny<User>())).Returns(() => $"accessToken{Guid.NewGuid()}");
            tokenMock.Setup(x => x.GetPrincipalFromExpiredToken(It.IsAny<string>(), It.IsAny<bool>())).Returns(new ClaimsPrincipal(
                new[] {
                    new ClaimsIdentity(new[] {
                        new Claim(ClaimsIdentity.DefaultNameClaimType, "test"),
                        new Claim(ClaimsIdentity.DefaultRoleClaimType, "test"),
                        new Claim(ClaimsIdentity.DefaultIssuer, "test"),
                        new Claim("http://schemas.xmlsoap.org/ws/2005/05/identity/claims/salt", Guid.NewGuid().ToString())
                    })
                }
            ));
            var mock = new Mock<IAuthDataProvider>();
            mock.Setup(x => x.Users).Returns(new List<User>
            {
                new User { Id = 1, Email = "test", PasswordHash = "test", Role = new Role { Name = "User" } }
            }.AsQueryable());
            mock.Setup(x => x.Roles).Returns(new List<Role> { new Role { Id = 1, Name = "User" } }.AsQueryable());
            authService = new AuthService(mock.Object, Mock.Of<ICryptService>(x => x.CreateHash(It.IsAny<string>()) == "test"), tokenMock.Object);
        }

        private void ValidateModel(LoginResult res)
        {
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.AccessToken);
            Assert.IsNotNull(res.RefreshToken);
        }

        [TestMethod]
        public async Task LoginTest()
        {
            var res = await authService.LoginAsync(new LoginModel { Login = "test", Password = "test" });
            ValidateModel(res);
        }

        [TestMethod]
        public async Task RegisterTest()
        {
            var res = await authService.RegisterAsync(new RegisterModel { Email = "test1", Nickname = "test", Password = "test" });
            ValidateModel(res);
        }

        [TestMethod]
        public async Task RestorePassword()
        {
            var res = await authService.RestorePassword(new PasswordRestore { PrevPassword = "test", Password = "test2", UserId = 1 }, string.Empty);
            ValidateModel(res);
        }

        [TestMethod]
        public async Task RefreshToken()
        {
            var resLogin = await authService.LoginAsync(new LoginModel { Login = "test", Password = "test" });
            var refreshData = await authService.RefreshToken(resLogin.RefreshToken, resLogin.AccessToken);

            Assert.IsNotNull(refreshData);
            Assert.AreNotEqual(resLogin.AccessToken, refreshData.AccessToken);
            Assert.AreNotEqual(resLogin.RefreshToken, refreshData.RefreshToken);
        }
    }
}
