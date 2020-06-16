using Microsoft.EntityFrameworkCore;
using SeacServer.Models;
using SeacServer.Settings;
using System;
using System.IO;
using System.Linq;

namespace SeacServer.Data
{
    public interface IDatabaseContext
    {
        public IQueryable<Application> Applications { get; }
        public void Apply();
        void UploadLocalProjects();
    }

    public class DatabaseContext : DbContext, IDatabaseContext
    {
        private readonly RuntimeSettings runtimeSettings;

        public DatabaseContext(DbContextOptions options, RuntimeSettings runtimeSettings) : base(options)
        {
            this.runtimeSettings = runtimeSettings;
        }

        public DbSet<Application> Applications { get; set; }
        public DbSet<ApplicationRelease> ApplicationReleases { get; set; }

        IQueryable<Application> IDatabaseContext.Applications => this.Applications;

        public void Apply() => Database.Migrate();

        public void UploadLocalProjects()
        {
            foreach (var directory in Directory.GetDirectories(runtimeSettings.Repo))
            {
                var parts = Path.GetFileName(directory).Split("_");
                var exec = (ExecuteMode)Enum.Parse(typeof(ExecuteMode), parts[2], true);
                if (!Applications.Any(x => x.Name == parts[0] && x.Platform == parts[1] && x.ExecuteMode == exec))
                {
                    Applications.Add(new Application
                    {
                        Developer = "system",
                        ExecuteMode = exec,
                        Name = parts[0],
                        Platform = parts[1],
                        Version = "1.0.0"
                    });
                }
            }

            SaveChanges();
        }
    }
}
