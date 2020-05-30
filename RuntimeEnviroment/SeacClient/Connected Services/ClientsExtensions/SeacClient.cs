using CommonCoreLibrary.APIClient;
using CommonCoreLibrary.Auth.Interfaces;
using Microsoft.AspNetCore.Http;
using System.Net.Http;
using System.Threading.Tasks;

namespace SeacClient.SeacRuntime
{
    public partial class SeacRuntimeClient : BaseAPIClient
    {
        private Task<byte[]> stream;

        public SeacRuntimeClient(IHttpContextAccessor httpContextAccessor, IBaseTokenService tokenService, IAuthBaseAPIClient authBaseAPIClient, HttpClient httpClient, string url) : base(httpContextAccessor, tokenService)
        {
            this.AuthAPIClient = authBaseAPIClient;
            this._httpClient = httpClient;
            this._baseUrl = url;
        }

        public Task<byte[]> Stream => stream;

        private async Task ProcessResponse(System.Net.Http.HttpResponseMessage response)
        {
            if (response.IsSuccessStatusCode)
                stream = response.Content.ReadAsByteArrayAsync();
        }

        partial void ProcessResponse(System.Net.Http.HttpClient client, System.Net.Http.HttpResponseMessage response)
        {
            ProcessResponse(response).GetAwaiter().GetResult();
        }
    }

    public static class SeacClientExtension
    {
        public static async Task<byte[]> CallStream(this ISeacRuntimeClient seacRuntime, Task task)
        {
            await task;
            return await ((SeacRuntimeClient)seacRuntime).Stream;
        }
    }
}
