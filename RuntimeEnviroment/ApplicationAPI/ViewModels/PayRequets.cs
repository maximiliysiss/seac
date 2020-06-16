using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationAPI.ViewModels
{
    public enum PayStyle
    {
        Phone,
        Card
    }

    public class PayRequets
    {
        public decimal Price { get; set; }
        public string User { get; set; }
        public int ApplicationId { get; set; }
        public PayStyle PayStyle { get; set; }
    }
}
