using SeacServer.Data;
using SeacServer.Exceptions;
using SeacServer.Models;
using SeacServer.Settings;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace SeacServer.Services
{
    public class ExecuteResult
    {
        public Stream CodeStream { get; set; }
    }

    public interface IRuntimeService
    {
        ExecuteResult Execute(string name, string platform, string mode);
    }


    public class RuntimeService: IRuntimeService
    {
        private readonly DatabaseContext databaseContext;
        private readonly RuntimeSettings runtimeSettings;

        public RuntimeService(DatabaseContext databaseContext, RuntimeSettings runtimeSettings)
        {
            this.databaseContext = databaseContext;
            this.runtimeSettings = runtimeSettings;
        }

        public ExecuteResult Execute(string name, string platform, string mode)
        {
            var application = databaseContext.Applications.FirstOrDefault(x => x.Name == name && x.Platform == platform);
            if (application == null)
                return null;
            switch ((ExecuteMode)Enum.Parse(typeof(ExecuteMode), mode, true))
            {
                case ExecuteMode.Single:
                    throw new ExecuteException("Single not executed");
                case ExecuteMode.Remote:
                    return RemoteExecute(application);
                case ExecuteMode.FullRemote:
                    break;
            }

            return null;
        }

        private ExecuteResult RemoteExecute(Application application)
        {
            var uri = Path.Combine(runtimeSettings.Repo, $"{application.Name}_{application.Platform}_{application.ExecuteMode.ToString().ToLower()}", $"{application.Name}.seac");
            FileStream fileStream = new FileStream(uri, FileMode.Open);
            return new ExecuteResult
            {
                CodeStream = fileStream
            };
        }
    }
}
