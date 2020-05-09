using Microsoft.EntityFrameworkCore;
using SeacServer.Models;
using System.Linq;

namespace SeacServer.Data
{
    public interface IDatabaseContext
    {
        public IQueryable<Application> Applications { get; }
        public void Apply();
    }

    public class DatabaseContext : DbContext, IDatabaseContext
    {
        public DatabaseContext(DbContextOptions options) : base(options)
        {
        }

        public DbSet<Application> Applications { get; set; }

        IQueryable<Application> IDatabaseContext.Applications => this.Applications;

        public void Apply() => Database.Migrate();
    }
}
