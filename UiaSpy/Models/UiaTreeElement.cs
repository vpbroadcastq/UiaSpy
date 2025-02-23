using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.ComponentModel;
using FlaUI.Core;
using FlaUI.Core.Identifiers;

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
			Details.Add(new UiaTreeEntryDetails("ToString()", Element.ToString()));

			//
			// Patterns
			//
			FlaUI.Core.Identifiers.PatternId[] elementPatterns = Element.GetSupportedPatterns();
			FlaUI.Core.Identifiers.PatternId[] allPatterns = Element.Automation.PatternLibrary.AllForCurrentFramework;
			foreach (PatternId pattern in allPatterns)
			{
				bool hasPattern = elementPatterns.Contains(pattern);
				Details.Add(new UiaTreeEntryDetails(pattern.Name + "Pattern", hasPattern ? "Yes" : "No"));
			}

			//
			// Properties
			//
			Details.Add(new UiaTreeEntryDetails("AutomationId", Element.Properties.AutomationId.ToString()));
			Details.Add(new UiaTreeEntryDetails("Name", Element.Properties.Name.ToString()));
			Details.Add(new UiaTreeEntryDetails("ClassName", Element.Properties.ClassName.ToString()));
			Details.Add(new UiaTreeEntryDetails("ControlType", Element.Properties.ControlType.ToString()));
			Details.Add(new UiaTreeEntryDetails("LocalizedControlType", Element.Properties.LocalizedControlType.ToString()));
			Details.Add(new UiaTreeEntryDetails("FrameworkType", Element.FrameworkType.ToString()));
			Details.Add(new UiaTreeEntryDetails("FrameworkId", Element.Properties.FrameworkId.ToString()));
			Details.Add(new UiaTreeEntryDetails("ProcessId", Element.Properties.ProcessId.ToString()));
			Details.Add(new UiaTreeEntryDetails("IsEnabled", Element.Properties.IsEnabled.ToString()));
			Details.Add(new UiaTreeEntryDetails("IsOffscreen", Element.Properties.IsOffscreen.ToString()));
			Details.Add(new UiaTreeEntryDetails("BoundingRectangle", Element.Properties.BoundingRectangle.ToString()));
			Details.Add(new UiaTreeEntryDetails("HelpText", Element.Properties.HelpText.ToString()));
			Details.Add(new UiaTreeEntryDetails("IsPassword", Element.Properties.IsPassword.ToString()));
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


