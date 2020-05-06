using Ninject;
using Ninject.Modules;
using System.Collections.Generic;
using System.Reflection;

namespace SeacClient.Services
{
    public interface IInjectContainer
    {
        T Resolve<T>();
        void Bind<It, T>() where T : It;
        void Bind<It, T>(Dictionary<string, object> args) where T : It;
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

        public T Resolve<T>() => standardKernel.Get<T>();
    }


    public class ApplicationNinject : NinjectModule
    {
        public override void Load()
        {
            Bind<INotificationService>().To<NotificationService>();
        }
    }
}
