using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace UiaSpy.Models
{
	public class UiaTreeEntryDetails : INotifyPropertyChanged
	{
		private string _value = null;
		private string _key = null;
		public event PropertyChangedEventHandler PropertyChanged = delegate { };
		
		public UiaTreeEntryDetails(string key, string value)
		{
			_key = key;
			_value = value;
		}
		public string Key
		{
			get { return _key; }
			set
			{
				_key = value;
				OnPropertyChanged();
			}
		}
		public string Value
		{
			get { return _value; }
			set
			{
				_value = value;
				OnPropertyChanged();
			}
		}
		public string Display
		{
			get { return _key + ":\t" + _value; }
		}

		public void OnPropertyChanged([CallerMemberName] string propertyName = null)
		{
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
		}
	}
}
