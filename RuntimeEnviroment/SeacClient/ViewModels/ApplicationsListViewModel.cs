using SeacClient.SeacRuntime;
using System.Collections.Generic;
using System.Linq;
using System.Windows;

namespace SeacClient.ViewModels
{
    public class ApplicationsListViewModel
    {
        public IEnumerable<ApplicationViewModel> Applications { get; private set; }
        public string Title { get; private set; }
        public Visibility VisibleAdd { get; set; }

        public ApplicationsListViewModel(ISeacRuntimeClient seacRuntimeClient, string title, Visibility visibility)
        {
            VisibleAdd = visibility;
            Title = title;
            Applications = seacRuntimeClient.ApiApplicationAsync().GetAwaiter().GetResult().Select(x => ApplicationViewModel.CreateViewModel(x, seacRuntimeClient));
        }
    }
}
