using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SeacClient.Pages
{
    /// <summary>
    /// Interaction logic for StorePage.xaml
    /// </summary>
    public partial class StorePage : Page
    {
        public StorePage()
        {
            InitializeComponent();
            this.Loaded += async (s, e) => await StorePageLoaded();
        }

        private async Task StorePageLoaded()
        {
            ISeacRuntimeClient seacRuntimeClient = new SeacRuntimeClient("https://localhost:5001", new System.Net.Http.HttpClient());
            var tmps = await seacRuntimeClient.ApiApplicationAsync();
        }
    }
}
