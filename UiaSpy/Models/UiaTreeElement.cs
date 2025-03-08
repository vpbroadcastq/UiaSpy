using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.ComponentModel;
using FlaUI.Core;
using FlaUI.Core.Identifiers;
using FlaUI.Core.Conditions;
using System.DirectoryServices;

namespace UiaSpy.Models
{
	public class UiaTreeEntry : INotifyPropertyChanged
	{
		public FlaUI.Core.AutomationElements.AutomationElement Element { get; set; }
		private string _name;
		private bool _isSelected = false;
		private bool _isExpanded = false;
		private Microsoft.UI.Dispatching.DispatcherQueue _mainWindowDq;
		private FlaUI.UIA3.UIA3Automation _automation;
		public event PropertyChangedEventHandler PropertyChanged;
		private Action<FlaUI.Core.AutomationElements.AutomationElement, FlaUI.Core.Definitions.StructureChangeType, int[]> StructureChangedHandler;
		public ObservableCollection<UiaTreeEntry> Children { get; set; }
		public ObservableCollection<UiaTreeEntryDetails> Details { get; set; }

		public UiaTreeEntry(FlaUI.Core.AutomationElements.AutomationElement e, FlaUI.UIA3.UIA3Automation a, Microsoft.UI.Dispatching.DispatcherQueue dq)
		{
			Element = e;
			_mainWindowDq = dq;
			_automation = a;
			StructureChangedHandler = OnStructureChanged;
			Children = new ObservableCollection<UiaTreeEntry>();
			Details = new ObservableCollection<UiaTreeEntryDetails>();

			PopulateChildren();
		}

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

		private void PopulateChildren()
		{
			FlaUI.Core.ITreeWalker tw = _automation.TreeWalkerFactory.GetRawViewWalker();
			FlaUI.Core.AutomationElements.AutomationElement currAe = tw.GetFirstChild(this.Element);
			while (currAe != null)
			{
				UiaTreeEntry currEntry = new UiaTreeEntry(currAe, _automation, _mainWindowDq);
				Children.Add(currEntry);
				currAe = tw.GetNextSibling(currAe);
			}
		}
		private void VerifyAndReorderChildren()
		{
			//...
		}

		private void RegisterForStructureChangedEvents()
		{
			Element.RegisterStructureChangedEvent(FlaUI.Core.Definitions.TreeScope.Children, this.StructureChangedHandler);
		}
		private void UnregisterForStructureChangedEvents()
		{
			// FrameworkAutomationElement has an UnregisterStructureChangedEventHandler but AutomationElement
			// doesn't expose it???
			// Element.UnregisterStructureChangedEventHandler(this.StructureChangedHandler);
		}
		private void OnStructureChanged(FlaUI.Core.AutomationElements.AutomationElement element, FlaUI.Core.Definitions.StructureChangeType changeType, int[] runtimeIds)
		{
			if (changeType == FlaUI.Core.Definitions.StructureChangeType.ChildRemoved)
			{
				_mainWindowDq.TryEnqueue(() =>
				{
					RemoveChild(element);
					OnPropertyChanged(nameof(Children));
				});
			}
			else if (changeType == FlaUI.Core.Definitions.StructureChangeType.ChildAdded)
			{
				_mainWindowDq.TryEnqueue(() =>
				{
					AddChild(element);
					OnPropertyChanged(nameof(Children));
				});
			}
		}

		private void RemoveChild(FlaUI.Core.AutomationElements.AutomationElement element)
		{
			foreach (UiaTreeEntry currChild in Children)
			{
				if (currChild.Element == element)
				{
					Children.Remove(currChild);
				}
			}
		}
		// Note that given a random element this won't add it in the right place - it will put it at the end
		// of the array.  The children might need to be resorted afterwards.
		private void AddChild(FlaUI.Core.AutomationElements.AutomationElement element)
		{
			UiaTreeEntry currEntry = new UiaTreeEntry(element, _automation, _mainWindowDq);
			Children.Add(currEntry);
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
			CacheRequest cr = new CacheRequest();

			cr.TreeScope = FlaUI.Core.Definitions.TreeScope.Element;
			cr.Add(Element.Automation.PropertyLibrary.Element.AutomationId);
			cr.Add(Element.Automation.PropertyLibrary.Element.Name);
			cr.Add(Element.Automation.PropertyLibrary.Element.ClassName);
			cr.Add(Element.Automation.PropertyLibrary.Element.ControlType);
			cr.Add(Element.Automation.PropertyLibrary.Element.LocalizedControlType);
			cr.Add(Element.Automation.PropertyLibrary.Element.FrameworkId);
			cr.Add(Element.Automation.PropertyLibrary.Element.ProcessId);
			cr.Add(Element.Automation.PropertyLibrary.Element.IsEnabled);
			cr.Add(Element.Automation.PropertyLibrary.Element.IsOffscreen);
			cr.Add(Element.Automation.PropertyLibrary.Element.BoundingRectangle);
			cr.Add(Element.Automation.PropertyLibrary.Element.HelpText);
			cr.Add(Element.Automation.PropertyLibrary.Element.IsPassword);
			cr.Add(Element.Automation.PropertyLibrary.Element.ControlType);
			cr.Add(Element.Automation.PropertyLibrary.Element.Culture);
			cr.Add(Element.Automation.PropertyLibrary.Element.AcceleratorKey);
			cr.Add(Element.Automation.PropertyLibrary.Element.AccessKey);
			using (cr.Activate())
			{
				var cachedElem = Element.FindFirst(FlaUI.Core.Definitions.TreeScope.Element, FlaUI.Core.Conditions.TrueCondition.Default);
				Details.Add(new UiaTreeEntryDetails("AutomationId", cachedElem.Properties.AutomationId.ToString()));
				Details.Add(new UiaTreeEntryDetails("Name", cachedElem.Properties.Name.ToString()));
				Details.Add(new UiaTreeEntryDetails("ClassName", cachedElem.Properties.ClassName.ToString()));
				Details.Add(new UiaTreeEntryDetails("ControlType", cachedElem.Properties.ControlType.ToString()));
				Details.Add(new UiaTreeEntryDetails("LocalizedControlType", cachedElem.Properties.LocalizedControlType.ToString()));
				Details.Add(new UiaTreeEntryDetails("FrameworkId", cachedElem.Properties.FrameworkId.ToString()));
				Details.Add(new UiaTreeEntryDetails("ProcessId", cachedElem.Properties.ProcessId.ToString()));
				Details.Add(new UiaTreeEntryDetails("IsEnabled", cachedElem.Properties.IsEnabled.ToString()));
				Details.Add(new UiaTreeEntryDetails("IsOffscreen", cachedElem.Properties.IsOffscreen.ToString()));
				Details.Add(new UiaTreeEntryDetails("BoundingRectangle", cachedElem.Properties.BoundingRectangle.ToString()));
				Details.Add(new UiaTreeEntryDetails("HelpText", cachedElem.Properties.HelpText.ToString()));
				Details.Add(new UiaTreeEntryDetails("IsPassword", cachedElem.Properties.IsPassword.ToString()));
				Details.Add(new UiaTreeEntryDetails("ControlType", cachedElem.Properties.ControlType.ToString()));
				Details.Add(new UiaTreeEntryDetails("Culture", cachedElem.Properties.Culture.ToString()));
				Details.Add(new UiaTreeEntryDetails("AcceleratorKey", cachedElem.Properties.AcceleratorKey.ToString()));
				Details.Add(new UiaTreeEntryDetails("AccessKey", cachedElem.Properties.AccessKey.ToString()));
			}
		}
	}
}


