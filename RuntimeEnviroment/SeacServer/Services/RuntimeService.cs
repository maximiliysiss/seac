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
        ExecuteResult Next(string name, string platform, string mode, string next);
    }


    public class RuntimeService : IRuntimeService
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
            ExecuteMode executeMode = (ExecuteMode)Enum.Parse(typeof(ExecuteMode), mode, true);
            var application = databaseContext.Applications.FirstOrDefault(x => x.Name == name && x.Platform == platform && x.ExecuteMode == executeMode);
            if (application == null)
                return null;
            switch (executeMode)
            {
                case ExecuteMode.Single:
                case ExecuteMode.Remote:
                case ExecuteMode.FullRemote:
                    return RemoteExecute(application);
            }

            return null;
        }

        public ExecuteResult Next(string name, string platform, string mode, string next)
        {
            ExecuteMode executeMode = (ExecuteMode)Enum.Parse(typeof(ExecuteMode), mode, true);
            var application = databaseContext.Applications.FirstOrDefault(x => x.Name == name && x.Platform == platform && x.ExecuteMode == executeMode);
            if (application == null)
                return null;

            var uri = Path.Combine(runtimeSettings.Repo, $"{application.Name}_{application.Platform}_{application.ExecuteMode.ToString().ToLower()}", $"{next}.seac");
            FileStream fileStream = new FileStream(uri, FileMode.Open);
            return new ExecuteResult
            {
                CodeStream = fileStream
            };
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
