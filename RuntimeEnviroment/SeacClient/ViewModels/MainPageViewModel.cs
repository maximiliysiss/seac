using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Navigation;

namespace SeacClient.ViewModels
{
    public class MainPageViewModel : INotifyPropertyChanged
    {
        public MainPageViewModel()
        {
        }

        public MainPageViewModel(Page content)
        {
            Source = content;
        }

        public Page Source { get; set; }
        public Brush Color { get; set; } = new SolidColorBrush(System.Windows.Media.Color.FromRgb(179, 144, 227));

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        public void NavigateAsync(Page page)
        {
            if (page.Uid != Source.Uid)
            {
                var prev = Source;
                Source = page;
                ((NavigationWindow)Window.GetWindow(prev)).RemoveBackEntry();
            }
            OnPropertyChanged(nameof(Source));
        }

        public void GoBack()
        {
            var service = Source.NavigationService;
            service.GoBack();
        }
    }
}
