using MaterialDesignThemes.Wpf;
using SeacClient.ViewModels;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for StorePage.xaml
    /// </summary>
    public partial class StorePage : Page
    {
        private readonly StoreViewModel storeViewModel;

        public StorePage(StoreViewModel storeViewModel)
        {
            InitializeComponent();
            this.DataContext = this.storeViewModel = storeViewModel;
            this.Loaded += async (s, e) => await storeViewModel.Load();
        }

        private async void Card_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e) => await ((ApplicationViewModel)((Card)sender).DataContext).OnClickAsync();

        private async void CreateShortCut(object sender, System.Windows.RoutedEventArgs e) => await ((ApplicationViewModel)((MenuItem)sender).DataContext).CreateShortCut();
    }
}
