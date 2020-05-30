using MaterialDesignThemes.Wpf;
using Microsoft.Win32;
using SeacClient.ViewModels;
using SeacClient.ViewModels.Applications;
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

        private void StartLocalApplication(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "ByteCode(*.seac)|*.seac",
                Multiselect = false
            };
            if (openFileDialog.ShowDialog() ?? false)
            {
                new LocalApplication(new SeacRuntime.ApplicationModel
                {
                    ExecuteMode = SeacRuntime.ExecuteMode._0,
                    Name = openFileDialog.FileName
                }).OnClickAsync();
            }
        }
    }
}
