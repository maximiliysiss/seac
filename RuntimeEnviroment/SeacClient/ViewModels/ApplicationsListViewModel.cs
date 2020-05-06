using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SeacClient.ViewModels
{
    public class ApplicationsListViewModel
    {
        public IEnumerable<ApplicationViewModel> Applications { get; private set; }
        public string Title { get; private set; }

        public ApplicationsListViewModel(ISeacRuntimeClient seacRuntimeClient, string title)
        {
            Title = title;
            Applications = seacRuntimeClient.ApiApplicationAsync().GetAwaiter().GetResult().Select(x => ApplicationViewModel.CreateViewModel(x, seacRuntimeClient));
        }
    }
}
