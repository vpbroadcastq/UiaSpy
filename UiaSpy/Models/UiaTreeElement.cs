using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace UiaSpy.Models
{
	public class UiaTreeEntry
	{
		public FlaUI.Core.AutomationElements.AutomationElement Element { get; set; }
		private string _name;
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
		public ObservableCollection<UiaTreeEntry> Children {get; set;}

		public UiaTreeEntry(FlaUI.Core.AutomationElements.AutomationElement e)
		{
			Element = e;
			Children = new ObservableCollection<UiaTreeEntry>();
		}
	}
}


