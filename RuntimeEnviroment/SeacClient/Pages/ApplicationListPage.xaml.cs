using MaterialDesignThemes.Wpf;
using SeacClient.ViewModels;
using System.Windows.Controls;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for ApplicationListPage.xaml
    /// </summary>
    public partial class ApplicationListPage : Page
    {
        public ApplicationListPage(ApplicationsListViewModel applicationsListViewModel)
        {
            InitializeComponent();
            this.DataContext = applicationsListViewModel;
        }

        private async void Card_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e) => await ((ApplicationViewModel)((Card)sender).DataContext).OnClickAsync();
    }
}
