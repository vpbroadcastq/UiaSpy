using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.ComponentModel;

namespace UiaSpy.Models
{
	public class UiaTreeEntry : INotifyPropertyChanged
	{
		public FlaUI.Core.AutomationElements.AutomationElement Element { get; set; }
		private string _name;
		private bool _isSelected = false;
		public event PropertyChangedEventHandler PropertyChanged;
		protected void OnPropertyChanged(string propertyName) =>
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));

		public string Name
		{
			get
			{
				_name = Element.Properties.ClassName.ValueOrDefault;
				if (_name != null && _name.Length>0)
				{
					return _name;
				}
				_name = Element.Properties.Name.ValueOrDefault;
				if (_name != null && _name.Length > 0)
				{
					return _name;
				}
				_name = Element.Properties.LocalizedControlType.ValueOrDefault;
				if (_name != null && _name.Length > 0)
				{
					return _name;
				}
				_name = "Unknown element";
				return _name;
			}
		}

		public bool IsSelected
		{
			get { return _isSelected; }
			set
			{
				if (_isSelected == value) { return; }
				LoadItemDetails();
				_isSelected = true;
				OnPropertyChanged(nameof(_isSelected));  // What is the correct arg?
			}
		}

		private void LoadItemDetails()
		{
			var itemDetails = new UiaTreeEntryDetails();
			itemDetails.Value = Element.ToString();
			Details.Add(itemDetails);
		}

		public ObservableCollection<UiaTreeEntry> Children {get; set;}
		public ObservableCollection<UiaTreeEntryDetails> Details { get; set; }

		public UiaTreeEntry(FlaUI.Core.AutomationElements.AutomationElement e)
		{
			Element = e;
			Children = new ObservableCollection<UiaTreeEntry>();
			Details = new ObservableCollection<UiaTreeEntryDetails>();
		}
	}
}


