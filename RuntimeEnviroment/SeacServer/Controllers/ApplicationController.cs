using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using SeacServer.Data;
using SeacServer.Services;
using SeacServer.ViewModels;

namespace SeacServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ApplicationController : ControllerBase
    {
        private readonly IDatabaseContext databaseContext;
        private readonly IMapperService mapperService;

        public ApplicationController(IDatabaseContext databaseContext, IMapperService mapperService)
        {
            this.databaseContext = databaseContext;
            this.mapperService = mapperService;
        }

        [HttpGet]
        public ActionResult<List<ApplicationModel>> GetApplicationModels()
        {
            return databaseContext.Applications.Select(x => mapperService.Map<ApplicationModel>(x)).ToList();
        }
    }
}