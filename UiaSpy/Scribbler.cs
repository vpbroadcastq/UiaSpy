using FlaUI.Core.Overlay;
using FlaUI.Core.WindowsAPI;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Printing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UiaSpy
{
	public class TransparentWindow : System.Windows.Forms.Form
	{
		public TransparentWindow()
		{
			FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			ShowInTaskbar = false;
			Visible = false;
		}
		protected override bool ShowWithoutActivation => true;

		protected override CreateParams CreateParams
		{
			get
			{
				var createParams = base.CreateParams;
				createParams.ExStyle |= (int)WindowStyles.WS_EX_TRANSPARENT;
				createParams.ExStyle |= (int)WindowStyles.WS_EX_TOOLWINDOW;
				createParams.ExStyle |= (int)WindowStyles.WS_EX_TOPMOST;
				//createParams.ExStyle |= (int)WindowStyles.WS_EX_LAYERED;
				return createParams;
			}
		}
	}

	public class Scribbler
	{
		public int Thickness = 5;
		private TransparentWindow _window = new TransparentWindow();
		public Scribbler()
		{
			//SetLayeredWindowAttributes(_window.Handle, 0, )
		}


		//
		// P/Invoke decls
		//
		[DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true, SetLastError = true)]
		internal static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
		[DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true, SetLastError = true)]

		[return: MarshalAs(UnmanagedType.Bool)]
		internal static extern bool SetWindowPos(IntPtr hWnd, IntPtr hwndAfter, int x, int y, int width, int height, int flags);

		/*[DllImport("user32.dll", EntryPoint = "GetWindowLongPtr")]
		private static extern IntPtr GetWindowLongPtr(IntPtr hWnd, int nIndex);

		[DllImport("user32.dll", EntryPoint = "SetWindowLongPtr")]
		private static extern IntPtr SetWindowLongPtr64(HandleRef hWnd, int nIndex, IntPtr dwNewLong);*/

		[DllImport("user32.dll")]
		public static extern bool SetLayeredWindowAttributes(IntPtr hwnd, uint crKey, byte bAlpha, uint dwFlags);

		//
		// Drawing
		//
		public void DrawRect(System.Drawing.Rectangle rectangle, System.Drawing.Color color, TimeSpan duration)
		{
			var leftBorder = new System.Drawing.Rectangle(rectangle.X, rectangle.Y, Thickness, rectangle.Height);
			var topBorder = new System.Drawing.Rectangle(rectangle.X, rectangle.Y, rectangle.Width, Thickness);
			var rightBorder = new System.Drawing.Rectangle(rectangle.X + rectangle.Width - Thickness, rectangle.Y, Thickness, rectangle.Height);
			var bottomBorder = new System.Drawing.Rectangle(rectangle.X, rectangle.Y + rectangle.Height - Thickness, rectangle.Width, Thickness);
			var allBorders = new[] { leftBorder, topBorder, rightBorder, bottomBorder };

			var gdiColor = System.Drawing.Color.FromArgb(color.A, color.R, color.G, color.B);
			_window.BackColor = gdiColor;

			_window.Paint += (s, e) => {
				using (Pen pen = new Pen(Color.Red, 15))
				{
					e.Graphics.DrawRectangle(pen, rectangle);
				}
			};

			SetWindowPos(_window.Handle, new IntPtr(-1), rectangle.X, rectangle.Y,
				rectangle.Width+5, rectangle.Height+5, SetWindowPosFlags.SWP_NOACTIVATE);
			ShowWindow(_window.Handle, ShowWindowTypes.SW_SHOWNA);

			/*System.Drawing.Graphics g = _window.CreateGraphics();
			Pen redPen = new Pen(Color.Red, 15);
			g.DrawRectangle(redPen, rectangle);*/

			Thread.Sleep(duration);
			_window.Hide();
			_window.Close();
			_window.Dispose();
		}
	}
}
