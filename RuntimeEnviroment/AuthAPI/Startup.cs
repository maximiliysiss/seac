using AuthAPI.Services;
using AuthAPI.Settings;
using Castle.Core.Logging;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.OpenApi.Models;

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
            var authSettings = Configuration.GetSection("AuthSettings").Get<AuthSettings>();

            services.AddSingleton(authSettings);
            services.AddDbContext<IAuthDataProvider, AuthDataProvider>(x => x.UseLazyLoadingProxies().UseSqlServer(Configuration.GetConnectionString("SQLServer")), ServiceLifetime.Scoped);
            services.AddScoped<IAuthService, AuthService>();
            services.AddScoped<ITokenService, TokenService>();
            services.AddScoped<ICryptService, CryptService>();
            services.AddTransient<IMapperService, AutoMapperService>();
            services.AddTransient<IUserService, UserService>();

            services.AddAuthentication(x =>
            {
                x.DefaultAuthenticateScheme = JwtBearerDefaults.AuthenticationScheme;
                x.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
            }).AddJwtBearer(x =>
            {
                x.TokenValidationParameters = new Microsoft.IdentityModel.Tokens.TokenValidationParameters
                {
                    ValidateAudience = true,
                    ValidateIssuer = true,
                    ValidateLifetime = true,
                    ValidAudience = authSettings.Audience,
                    ValidIssuer = authSettings.Issuer,
                    IssuerSigningKey = authSettings.SecurityKey
                };
            });

            services.AddSwaggerGen(c =>
            {
                c.SwaggerDoc("v1", new OpenApiInfo
                {
                    Title = Configuration["ApiInfo:Name"],
                    Version = Configuration["ApiInfo:Version"]
                });
            });

            services.AddControllers();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env, IAuthDataProvider authDataProvider, ILogger<Startup> logger)
        {
            logger.LogInformation($"Connection string: {Configuration.GetConnectionString("SQLServer")}");

            authDataProvider.ApplyChanges();

            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseHttpsRedirection();

            app.UseRouting();
            app.UseAuthentication();
            app.UseAuthorization();

            app.UseSwagger();

            app.UseSwaggerUI(c =>
            {
                c.SwaggerEndpoint("/swagger/v1/swagger.json", $"{Configuration["ApiInfo:Name"]} {Configuration["ApiInfo:Version"]}");
            });

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }
    }
}
