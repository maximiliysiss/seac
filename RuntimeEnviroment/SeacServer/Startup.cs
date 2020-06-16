using CommonCoreLibrary.Startup;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using SeacServer.Data;
using SeacServer.Services;
using SeacServer.Settings;

namespace SeacServer
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddControllers();
            services.AddSingleton(Configuration.GetSection("RuntimeSettings").Get<RuntimeSettings>());
            services.AddDbContext<IDatabaseContext, DatabaseContext>(x => x.UseSqlServer(Configuration.GetConnectionString("Default")), ServiceLifetime.Scoped);

            services.AddJwtAuth(Configuration);
            services.AddSwagger(Configuration["ApiInfo:Name"], Configuration["ApiInfo:Version"]);
            services.AddConsul(Configuration);

            services.AddScoped<IRuntimeService, RuntimeService>();
            services.AddSingleton<IMapperService, AutoMapperService>();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env, IHostApplicationLifetime hostApplicationLifetime, IDatabaseContext databaseContext)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            databaseContext.Apply();
            databaseContext.UploadLocalProjects();

            app.RegisterWithConsul(hostApplicationLifetime);

            app.UseHttpsRedirection();

            app.UseRouting();

            app.UseSwaggerWithUI(Configuration["ApiInfo:Name"], Configuration["ApiInfo:Version"]);
            app.UsePrometheusMetric();

            app.UseAuthorization();
            app.UseAuthentication();

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }
    }
}
