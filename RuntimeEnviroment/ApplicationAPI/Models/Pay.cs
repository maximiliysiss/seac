using ApplicationAPI.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationAPI.Models
{
    public class Pay
    {
        public int Id { get; set; }
        public DateTime DateTime { get; set; }
        public int ApplicationId { get; set; }
        public decimal Price { get; set; }
        public string UserId { get; set; }
        public PayStyle PayStyle { get; set; }
    }
}
