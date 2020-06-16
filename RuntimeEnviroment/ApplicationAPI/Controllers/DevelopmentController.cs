using Microsoft.AspNetCore.Mvc;

namespace ApplicationAPI.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class DevelopmentController : ControllerBase
    {
        [HttpPost]
        public ActionResult UploadApplcation() => Ok();
        [HttpPost]
        public ActionResult RegisterApplication() => Ok();
        [HttpPost]
        public ActionResult SetupSettings() => Ok();
    }
}