using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Navigation;

namespace SeacClient.ViewModels
{
    public class MaiPageViewModel : INotifyPropertyChanged
    {
        public MaiPageViewModel()
        {
        }

        public MaiPageViewModel(Page content)
        {
            Source = content;
        }

        public Page Source { get; set; }
        public Brush Color { get; set; } = new SolidColorBrush(System.Windows.Media.Color.FromRgb(179, 144, 227));

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        public void NavigateAsync(Page page)
        {
            var prev = Source;
            Source = page;
            ((NavigationWindow)Window.GetWindow(prev)).RemoveBackEntry();
            OnPropertyChanged(nameof(Source));
        }
    }
}
