using SeacClient.Services;
using SeacClient.ViewModels;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for MainPage.xaml
    /// </summary>
    public partial class MainPage : Page, INavigateWindow
    {
        private readonly MainPageViewModel mainPageViewModel;

        public MainPage(MainPageViewModel mainPageViewModel)
        {
            this.Uid = nameof(MainPage);
            InitializeComponent();
            this.DataContext = this.mainPageViewModel = mainPageViewModel;
        }

        private void HeaderMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                Window.GetWindow(this).DragMove();
                e.Handled = true;
            }
        }

        private void OnClose(object sender, RoutedEventArgs e) => Window.GetWindow(this).Close();
        private void OnMaximize(object sender, RoutedEventArgs e)
        {
            var wnd = Window.GetWindow(this);
            wnd.WindowState = wnd.WindowState == WindowState.Maximized ? WindowState.Normal : WindowState.Maximized;
        }
        private void OnMinimize(object sender, RoutedEventArgs e) => Window.GetWindow(this).WindowState = WindowState.Minimized;

        public void Navigate(Page page) => mainPageViewModel.NavigateAsync(page);

        public void GoBack() => mainPageViewModel.GoBack();
    }
}
