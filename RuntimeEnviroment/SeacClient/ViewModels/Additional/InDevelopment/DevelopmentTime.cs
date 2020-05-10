using System;
using System.Collections.Generic;
using System.Text;

namespace SeacClient.ViewModels.Additional.InDevelopment
{
    public class DevelopmentTimeViewModel
    {
        public DevelopmentTimeViewModel(int value, string name)
        {
            Value = value;
            Name = name;
        }

        public int Value { get; set; }
        public string Name { get; set; }
    }
}
