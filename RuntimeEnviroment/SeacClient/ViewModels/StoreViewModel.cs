using SeacClient.SeacRuntime;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeacClient.ViewModels
{
    public class StoreViewModel : INotifyPropertyChanged
    {
        public IEnumerable<ApplicationViewModel> StoreModels { get; private set; }
        public IEnumerable<ApplicationViewModel> ClientModels { get; private set; }

        private readonly ISeacRuntimeClient seacRuntimeClient;

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop = null) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        public StoreViewModel(ISeacRuntimeClient seacRuntimeClient)
        {
            this.seacRuntimeClient = seacRuntimeClient;
        }

        public async Task Load()
        {
            StoreModels = (await seacRuntimeClient.ApiApplicationAsync()).Select(x => ApplicationViewModel.CreateViewModel(x, seacRuntimeClient));
            ClientModels = (await seacRuntimeClient.ApiApplicationAsync()).Select(x => ApplicationViewModel.CreateViewModel(x, seacRuntimeClient));
            OnPropertyChanged("StoreModels");
            OnPropertyChanged("ClientModels");
        }
    }
}
