using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using SeacServer.Data;
using SeacServer.Services;

namespace SeacServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class RuntimeController : ControllerBase
    {
        private readonly IRuntimeService runtimeService;

        public RuntimeController(IRuntimeService runtimeService)
        {
            this.runtimeService = runtimeService;
        }

        [HttpGet("{name}/{platform}/{mode}")]
        public ActionResult<ExecuteResult> Execute(string name, string platform, string mode)
        {
            var res = runtimeService.Execute(name, platform, mode);
            if (res == null)
                return NotFound();
            return File(res.CodeStream, "application/octet-stream", $"{name}_{mode}_{platform}");
        }
    }
}