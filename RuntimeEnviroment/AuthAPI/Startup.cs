using AuthAPI.Services;
using AuthAPI.Settings;
using CommonCoreLibrary.Startup;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace AuthAPI
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
            services.AddDbContext<IAuthDataProvider, AuthDataProvider>(x => x.UseLazyLoadingProxies().UseSqlServer(Configuration.GetConnectionString("SQLServer")), ServiceLifetime.Scoped);
            services.AddScoped<IAuthService, AuthService>();
            services.AddScoped<ITokenService, TokenService>();
            services.AddScoped<ICryptService, CryptService>();
            services.AddTransient<IMapperService, AutoMapperService>();
            services.AddTransient<IUserService, UserService>();

            services.AddJwtAuth(Configuration);
            services.AddConsul(Configuration);
            services.AddSwagger(Configuration["ApiInfo:Name"], Configuration["ApiInfo:Version"]);
            services.AddControllers();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env, IAuthDataProvider authDataProvider, ILogger<Startup> logger, IHostApplicationLifetime hostApplicationLifetime)
        {
            logger.LogInformation($"Connection string: {Configuration.GetConnectionString("SQLServer")}");

            authDataProvider.ApplyChanges();
            app.RegisterWithConsul(hostApplicationLifetime);

            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseHttpsRedirection();

            app.UseRouting();
            app.UseAuthentication();
            app.UseAuthorization();

            app.UseSwaggerWithUI(Configuration["ApiInfo:Name"], Configuration["ApiInfo:Version"]);

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }
    }
}
