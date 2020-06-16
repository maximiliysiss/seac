using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace SeacClient.ViewModels
{
    public interface IButtonViewModel
    {
        string Text { get; }
        void OnClick();
    }

    public class MenuButtonViewModel : IButtonViewModel, INotifyPropertyChanged
    {
        private readonly string text;
        private readonly string uri;
        private readonly StoreViewModel storeViewModel;

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string prop = null) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));

        public string Text => text;
        public string Uri => uri;

        public MenuButtonViewModel(string text, string uri, StoreViewModel storeViewModel)
        {
            this.text = text;
            this.uri = uri;
            this.storeViewModel = storeViewModel;
        }

        private bool isSelected = false;
        public bool IsSelected
        {
            get => isSelected;
            set
            {
                isSelected = value;
                OnPropertyChanged(nameof(IsSelected));
            }
        }
        public void OnClick() => storeViewModel.NavigateTo(uri);
    }

    public class MenuContextViewModel : IButtonViewModel
    {
        private readonly string text;
        private readonly Action action;
        public string Text => text;

        public MenuContextViewModel(string text, Action action)
        {
            this.text = text;
            this.action = action;
        }

        public void OnClick() => action?.Invoke();
    }
}
