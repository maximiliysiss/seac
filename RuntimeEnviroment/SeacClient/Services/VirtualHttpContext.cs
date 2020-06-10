using AuthAPI.Settings;
using CommonCoreLibrary.Auth.Interfaces;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Features;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Security.Principal;
using System.Threading;
using System.Threading.Tasks;

namespace SeacClient.Services
{
    public class VirtualHttpContextAccessor : IHttpContextAccessor
    {
        public HttpContext HttpContext { get; set; } = new VirtualHttpContext
        {
            User = new ClaimsPrincipal(new VirtualIdentity(false))
        };
    }

    public class VirtualHttpContext : HttpContext
    {
        public override ConnectionInfo Connection => throw new NotImplementedException();

        public override IFeatureCollection Features => throw new NotImplementedException();

        public override IDictionary<object, object> Items { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public override HttpRequest Request => throw new NotImplementedException();

        public override CancellationToken RequestAborted { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override IServiceProvider RequestServices { get; set; } = new VirtualServiceProvider();

        public override HttpResponse Response => throw new NotImplementedException();

        public override ISession Session { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override string TraceIdentifier { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override ClaimsPrincipal User { get; set; }

        public override WebSocketManager WebSockets => throw new NotImplementedException();

        public override void Abort()
        {
            throw new NotImplementedException();
        }
    }

    public class VirtualIdentity : IIdentity
    {
        private readonly bool isAuth;

        public VirtualIdentity(bool isAuth = true)
        {
            this.isAuth = isAuth;
        }

        public string AuthenticationType => JwtBearerDefaults.AuthenticationScheme;

        public bool IsAuthenticated => isAuth;

        public string Name => string.Empty;
    }

    public class VirtualTokenService : ClientTokenService
    {
        public VirtualTokenService(AuthSettings authSettings, IHttpContextAccessor httpContextAccessor) : base(authSettings, httpContextAccessor)
        {
        }

        public override async Task SignInAsync(IAuthResult loginResult)
        {
            if (loginResult == null)
                return;
            var principal = GetPrincipalFromExpiredToken(loginResult.AccessToken);
            principal.Identities.First().AddClaim(new Claim("Token", loginResult.AccessToken));
            principal.Identities.First().AddClaim(new Claim("Refresh", loginResult.RefreshToken));
            /*for next request in this request*/
            httpContextAccessor.HttpContext.User = principal;
        }
    }

    public class VirtualServiceProvider : IServiceProvider
    {
        private readonly IAuthenticationService authenticationService = new VirtualIAuthService();

        public object GetService(Type serviceType)
        {
            return authenticationService;
        }
    }

    public class VirtualIAuthService : IAuthenticationService
    {
        public Task<AuthenticateResult> AuthenticateAsync(HttpContext context, string scheme)
        {
            throw new NotImplementedException();
        }

        public Task ChallengeAsync(HttpContext context, string scheme, AuthenticationProperties properties)
        {
            throw new NotImplementedException();
        }

        public Task ForbidAsync(HttpContext context, string scheme, AuthenticationProperties properties)
        {
            throw new NotImplementedException();
        }

        public Task SignInAsync(HttpContext context, string scheme, ClaimsPrincipal principal, AuthenticationProperties properties)
        {
            throw new NotImplementedException();
        }

        public async Task SignOutAsync(HttpContext context, string scheme, AuthenticationProperties properties)
        {
            context.User = new ClaimsPrincipal(new VirtualIdentity(false));
        }
    }
}
