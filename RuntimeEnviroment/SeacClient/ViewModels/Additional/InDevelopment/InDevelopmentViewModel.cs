using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Threading;

namespace SeacClient.ViewModels.Additional.InDevelopment
{
    public class InDevelopmentViewModel : INotifyPropertyChanged
    {
        public InDevelopmentViewModel()
        {
            GenerateTime();
            Timer timer = new Timer((x) =>
            {
                GenerateTime();
                OnPropertyChanged(nameof(DevelopmentTimes));
            }, null, 0, 1000);
        }

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        private void GenerateTime()
        {
            var now = new DateTime(2020, 12, 31) - DateTime.Now;
            DevelopmentTimes = new List<DevelopmentTimeViewModel>
            {
                new DevelopmentTimeViewModel(now.Days, "дней"),
                new DevelopmentTimeViewModel(now.Hours, "часов"),
                new DevelopmentTimeViewModel(now.Minutes, "минут"),
                new DevelopmentTimeViewModel(now.Seconds, "секунд")
            };
        }

        public List<DevelopmentTimeViewModel> DevelopmentTimes { get; set; }
    }
}
