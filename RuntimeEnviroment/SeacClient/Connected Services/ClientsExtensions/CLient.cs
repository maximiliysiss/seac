using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace SeacClient.SeacRuntime
{
    public partial class SeacRuntimeClient
    {
        private Task<byte[]> stream;
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
