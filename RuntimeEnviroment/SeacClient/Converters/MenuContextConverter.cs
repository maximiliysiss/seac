using SeacClient.ViewModels;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
using System.Windows.Controls;
using System.Windows.Data;

namespace SeacClient.Converters
{
    public class MenuContextConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is List<MenuContextViewModel> contextList)
            {
                var resList = new List<MenuItem>();
                foreach (var menuContextViewModel in contextList)
                {
                    var menuItem = new MenuItem { Header = menuContextViewModel.Text };
                    menuItem.Click += (s, e) => menuContextViewModel.OnClick();
                    resList.Add(menuItem);
                }
                return resList;
            }
            return null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
