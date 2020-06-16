using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ApplicationAPI.ViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace ApplicationAPI.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class PayController : ControllerBase
    {
        [HttpPost]
        public ActionResult PayRequest()
        {
            return Ok();
        }

        [HttpPost]
        public ActionResult PayConfirmed()
        {
            return Ok();
        }
    }
}