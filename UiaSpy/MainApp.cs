using FlaUI.UIA3;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using WinRT.UiaSpyVtableClasses;

namespace UiaSpy
{
	// Main data structure for app-lifetime data.  Owned by UiaSpy.App
	public class MainApp
	{
		public FlaUI.UIA3.UIA3Automation Automation = new UIA3Automation();
		public FlaUI.Core.Application AttachedApp;
		public MainApp()
		{
			//...
		}
	}
}
