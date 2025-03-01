using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.ComponentModel;
using FlaUI.Core;
using FlaUI.Core.Identifiers;
using System;

namespace UiaSpy.Models
{
	public class UiaTreeEntry : INotifyPropertyChanged
	{
		public FlaUI.Core.AutomationElements.AutomationElement Element { get; set; }
		private string _name;
		private bool _isSelected = false;
		private bool _isExpanded = false;
		public event PropertyChangedEventHandler PropertyChanged;
		private Action<FlaUI.Core.AutomationElements.AutomationElement, FlaUI.Core.Definitions.StructureChangeType, int[]> StructureChangedHandler;
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
				// TODO:  Do i not have any way to mark as no longer selected?
				if (_isSelected == value) { return; }
				if (value == true)
				{
					LoadItemDetails();
					_isSelected = true;
				}
				else
				{
					_isSelected = false;
					// TODO:  Should there be an UnloadItemDetails to force refetching should this element become
					// selected again?
				}
				OnPropertyChanged(nameof(_isSelected));  // What is the correct arg?
			}
		}
		public bool IsExpanded
		{
			get { return _isExpanded; }
			set
			{
				if (_isExpanded == value) { return; }
				_isExpanded = value;
				if (value == true)
				{
					RegisterForStructureChangedEvents();
				}
				else
				{
					UnregisterForStructureChangedEvents();
				}
				OnPropertyChanged(nameof(_isExpanded));  // What is the correct arg?
			}
		}
		private void RegisterForStructureChangedEvents()
		{
			Element.RegisterStructureChangedEvent(FlaUI.Core.Definitions.TreeScope.Element, this.StructureChangedHandler);
		}
		private void UnregisterForStructureChangedEvents()
		{
			// FrameworkAutomationElement has an UnregisterStructureChangedEventHandler but AutomationElement
			// doesn't expose it???
			// Element.UnregisterStructureChangedEventHandler(this.StructureChangedHandler);
		}
		private void OnStructureChanged(FlaUI.Core.AutomationElements.AutomationElement element, FlaUI.Core.Definitions.StructureChangeType changeType, int[] runtimeIds)
		{
			// This needs to be somehow communicated to the UI
			Children = new ObservableCollection<UiaTreeEntry>();
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
			StructureChangedHandler = OnStructureChanged;
			Children = new ObservableCollection<UiaTreeEntry>();
			Details = new ObservableCollection<UiaTreeEntryDetails>();
		}
	}
}


