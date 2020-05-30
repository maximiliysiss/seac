using CommonCoreLibrary.APIClient;
using CommonCoreLibrary.Auth.Interfaces;
using Microsoft.AspNetCore.Http;
using System.Net.Http;
using System.Threading.Tasks;

namespace SeacClient.AuthAPI
{
    public partial class AuthClient : BaseAPIClient, IAuthBaseAPIClient
    {
        public AuthClient(IHttpContextAccessor httpContextAccessor, IBaseTokenService tokenService, HttpClient httpClient, string url) : base(httpContextAccessor, tokenService)
        {
            this.AuthAPIClient = this;
            this._httpClient = httpClient;
            this._baseUrl = url;
        }

        public Task AuthLoginGetAsync()
        {
            return ApiAuthLoginGetAsync();
        }

        public async Task<IAuthResult> AuthRefreshtokenAsync(string v1, string v2)
        {
            return await ApiAuthRefreshtokenAsync(v1, v2);
        }
    }
}
