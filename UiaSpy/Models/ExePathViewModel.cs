using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace UiaSpy.Models
{
	public class ExePathViewModel : INotifyPropertyChanged
	{
		private string _value = "";
		public event PropertyChangedEventHandler PropertyChanged = delegate { };

		public ExePathViewModel()
		{
			Value = "D:\\bin\\BabelPad.exe";
		}

		public string Value
		{
			get { return _value; }
			set {
				_value = value;
				OnPropertyChanged();
			}
		}

		public void OnPropertyChanged([CallerMemberName] string propertyName = null)
		{
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
		}
	}
}
