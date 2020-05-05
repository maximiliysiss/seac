using Microsoft.AspNetCore.Mvc;
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
        public ActionResult Execute(string name, string platform, string mode)
        {
            var res = runtimeService.Execute(name, platform, mode);
            if (res == null)
                return NotFound();
            return File(res.CodeStream, "application/octet-stream", $"{name}_{mode}_{platform}");
        }

        [HttpGet("{name}/{platform}/{mode}/{next}")]
        public ActionResult Next(string name, string platform, string mode, string next)
        {
            var res = runtimeService.Next(name, platform, mode, next);
            if (res == null)
                return NotFound();
            return File(res.CodeStream, "application/octet-stream", $"{name}_{mode}_{platform}");
        }
    }
}