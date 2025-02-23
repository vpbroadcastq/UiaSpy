using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using FlaUI.UIA3;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using UiaSpy.Models;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage.Pickers;
using Windows.Storage;
using WinRT.Interop;
using Microsoft.UI.Windowing;
using Microsoft.UI;
using System.Runtime.InteropServices;


namespace UiaSpy
{
	public sealed partial class MainWindow : Window
	{
		public ObservableCollection<Models.UiaTreeEntry> UiaTreeEntries { get; set; } = new();
		public Models.ExePathViewModel ExePath { get; set; } = new();

		private MainApp _mainApp;
		private nint _hwnd;

		public MainWindow(MainApp mainApp)
		{
			_mainApp = mainApp;
			this.InitializeComponent();
			_hwnd = WindowNative.GetWindowHandle(this);
			RemoveRoundedCorners();
		}

		//
		// Event handlers for MainWindow UI elements
		//
		private void UiElement_UiaTreeTreeView_selectionChanged(object sender, TreeViewSelectionChangedEventArgs e)
		{
			// It's possible to select multiple elements in a TreeView but I can only display details of one node
			// at a time.  Should I populate the details of everything selected?
			// The update to the rhs pane can't tigger from a UiaTreeEntry.IsSelected -> true b/c there could be
			// multiple of them.  I need to decide _here_ which one to display in the rhs pane if multiple are
			// selected.
			if (e.AddedItems.Count == 1)
			{
				object selectedObj = e.AddedItems[0];
				UiaTreeEntry selectedEntry = (UiaTreeEntry)selectedObj;
				selectedEntry.IsSelected = true;
				UiElement_UiaNodeDetailsListView.ItemsSource = selectedEntry.Details;
				return;
			}
			else if (e.RemovedItems.Count == 1)
			{
				object deselectedObj = e.RemovedItems[0];
				UiaTreeEntry selectedEntry = (UiaTreeEntry)deselectedObj;
				selectedEntry.IsSelected = false;
			}
			UiElement_UiaNodeDetailsListView.ItemsSource = null;
		}
		private async void UiElement_BrowseExePathButton_Click(object sender, RoutedEventArgs e)
		{
			FileOpenPicker filePicker = new FileOpenPicker();
			InitializeWithWindow.Initialize(filePicker, _hwnd);
			filePicker.SuggestedStartLocation = PickerLocationId.Desktop;
			filePicker.FileTypeFilter.Add(".exe");

			StorageFile file = await filePicker.PickSingleFileAsync();
			if (file != null)
			{
				ExePath.Value = file.Path;
			}
		}
		private void UiElement_MyButton_Click(object sender, RoutedEventArgs e)
		{
			UiElement_MyButton.Content = "Clicked";
			Scribbler scrib = new Scribbler();
			System.Drawing.Rectangle rect = new(3007, 337, 1671, 893);
			scrib.DrawRect(rect,System.Drawing.Color.Blue, TimeSpan.FromMilliseconds(2000));
			//PopulateTree();
		}
		private void UiElement_LaunchExeButton_Click(object sender, RoutedEventArgs e)
		{
			if (LaunchApplication())
			{
				PopulateTree();
			}
		}

		//
		// Styling
		//
		[DllImport("dwmapi.dll")]
		private static extern int DwmSetWindowAttribute(IntPtr hwnd, int dwAttribute, ref int pvAttribute, int cbAttribute);
		private void RemoveRoundedCorners()
		{
			IntPtr hWnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
			const int DWMWA_WINDOW_CORNER_PREFERENCE = 33;
			int DWMWCP_DONOTROUND = 1; // Forces square corners
			DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, ref DWMWCP_DONOTROUND, sizeof(int));
		}

		//
		// Things that should probably not live on MainWindow
		//
		private bool LaunchApplication()
		{
			try
			{
				ProcessStartInfo processStart = new ProcessStartInfo(ExePath.Value);
				processStart.WorkingDirectory = "D:\\dev\\UiaSpy\\junk";
				_mainApp.AttachedApp = FlaUI.Core.Application.Launch(processStart);
			}
			catch (Exception ex)
			{
				ShowMessage(ex.Message);
				return false;
			}
			System.Threading.Thread.Sleep(3000);
			return true;
		}
		private async void ShowMessage(string msg)
		{
			ContentDialog dialog = new ContentDialog
			{
				Title = "Information",
				Content = msg,
				CloseButtonText = "OK",
				XamlRoot = this.Content.XamlRoot
			};

			await dialog.ShowAsync();
		}
		private void PopulateTree()
		{
			FlaUI.Core.AutomationElements.Window windowAe = _mainApp.AttachedApp.GetMainWindow(_mainApp.Automation);
			FlaUI.Core.ITreeWalker tw = _mainApp.Automation.TreeWalkerFactory.GetRawViewWalker();

			UiaTreeEntry windowEntry = new UiaTreeEntry(windowAe);
			UiaTreeEntries.Add(windowEntry);
			
			dfs(tw, windowEntry);
		}
		private void dfs(FlaUI.Core.ITreeWalker tw, UiaTreeEntry prevEntry)
		{
			FlaUI.Core.AutomationElements.AutomationElement currAe = tw.GetFirstChild(prevEntry.Element);
			while (currAe != null)
			{
				UiaTreeEntry currEntry = new UiaTreeEntry(currAe);
				prevEntry.Children.Add(currEntry);
				dfs(tw, currEntry);
				currAe = tw.GetNextSibling(currAe);
			}
		}
	}
}
