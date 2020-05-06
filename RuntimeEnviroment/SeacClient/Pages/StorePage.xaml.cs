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
        private readonly StoreViewModel storageViewModel;

        public StorePage(StoreViewModel storeViewModel)
        {
            InitializeComponent();
            this.DataContext = this.storageViewModel = storeViewModel;
            this.Loaded += async (s, e) => await storeViewModel.Load();
        }

        private void MenuButtonClick(object sender, System.Windows.Input.MouseButtonEventArgs e) => ((IButtonViewModel)((TextBlock)sender).DataContext).OnClick();

        private void OpenUserSettings(object sender, System.Windows.Input.MouseButtonEventArgs e) => storageViewModel.NavigateTo("usersettings");
    }
}
