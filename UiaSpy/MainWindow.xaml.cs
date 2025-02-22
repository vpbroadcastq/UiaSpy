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
		}

		void potato(object sender, TreeViewSelectionChangedEventArgs e)
		{
			object selectedObj = e.AddedItems[0];
			UiaTreeEntry selectedEntry = selectedObj as UiaTreeEntry;
			selectedEntry.IsSelected = true;
		}

		private void myButton_Click(object sender, RoutedEventArgs e)
        {
            myButton.Content = "Clicked";
            //PopulateTree();
		}
		private void launchExeButton_Click(object sender, RoutedEventArgs e)
		{
			if (LaunchApplication())
			{
				PopulateTree();
			}
		}
		private async void browseButton_Click(object sender, RoutedEventArgs e)
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
