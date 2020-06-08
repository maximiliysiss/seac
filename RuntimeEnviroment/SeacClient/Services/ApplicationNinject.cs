using AuthAPI.Settings;
using CommonCoreLibrary.Auth.Interfaces;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Configuration;
using Ninject;
using Ninject.Modules;
using SeacClient.AuthAPI;
using SeacClient.SeacRuntime;
using SeacClient.Settings;
using System.Collections.Generic;
using System.Reflection;

namespace SeacClient.Services
{
    public interface IInjectContainer
    {
        T Resolve<T>();
        void Bind<It, T>() where T : It;
        void Bind<It, T>(Dictionary<string, object> args) where T : It;
        void Init(IConfigurationRoot configurationRoot, RuntimeSettings runtimeSettings);
    }

    public class ApplicationContainer : IInjectContainer
    {
        private readonly StandardKernel standardKernel;

        public ApplicationContainer()
        {
            standardKernel = new StandardKernel();
            standardKernel.Load(Assembly.GetExecutingAssembly());
        }

        public void Bind<It, T>() where T : It => standardKernel.Bind<It>().To<T>();

        public void Bind<It, T>(Dictionary<string, object> args) where T : It
        {
            var bind = standardKernel.Bind<It>().To<T>();
            foreach (var arg in args)
                bind.WithConstructorArgument(arg.Key, arg.Value);
        }

        public void Init(IConfigurationRoot configurationRoot, RuntimeSettings runtimeSettings)
        {
            standardKernel.Inject(configurationRoot.GetSection("AuthSettings").Get<AuthSettings>());
            Bind<ISeacRuntimeClient, SeacRuntimeClient>(new Dictionary<string, object>
            {
                { "baseUrl", runtimeSettings.ServerRuntimeUrl},
                { "httpClient",new System.Net.Http.HttpClient()  }
            });
            Bind<IAuthClient, AuthClient>(new Dictionary<string, object>
            {
                { "baseUrl", runtimeSettings.ServerAuthUrl},
                { "httpClient",new System.Net.Http.HttpClient()  }
            });
        }

        public T Resolve<T>() => standardKernel.Get<T>();
    }


    public class ApplicationNinject : NinjectModule
    {
        public override void Load()
        {
            Bind<INotificationService>().To<NotificationService>();
            Bind<IHttpContextAccessor>().To<VirtualHttpContextAccessor>();
            Bind<IBaseTokenService>().To<VirtualTokenService>();
        }
    }
}
