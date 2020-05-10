using SeacClient.ViewModels.Additional.InDevelopment;
using System.Windows.Controls;

namespace SeacClient.Pages.Frames
{
    /// <summary>
    /// Interaction logic for InDevelopment.xaml
    /// </summary>
    public partial class InDevelopment : Page
    {
        public InDevelopment()
        {
            InitializeComponent();
            DataContext = new InDevelopmentViewModel();
        }
    }
}
