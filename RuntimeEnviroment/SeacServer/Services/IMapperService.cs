using AutoMapper;
using SeacServer.Models;
using SeacServer.ViewModels;

namespace SeacServer.Services
{
    public interface IMapperService
    {
        R Map<R>(object fromMap);
    }

    public class AutoMapperService : IMapperService
    {
        private readonly Mapper mapper;

        public AutoMapperService()
        {
            var config = new MapperConfiguration(x =>
            {
                x.CreateMap<Application, ApplicationModel>();
            });

            mapper = new Mapper(config);
        }

        public R Map<R>(object fromMap) => mapper.Map<R>(fromMap);
    }
}
