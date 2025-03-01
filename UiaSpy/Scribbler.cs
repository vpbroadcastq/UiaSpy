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
using Windows.Networking.Connectivity;

namespace UiaSpy
{
	// TODO:  It's awkward that the timer lives on TransparentWindow; it would be better if i could move it to
	// Scribbler.
	// TODO:  Need to .Dispose() the _window (and the _pen ?)
	public class TransparentWindow : System.Windows.Forms.Form
	{
		public System.Windows.Forms.Timer closeTimer;
		public TransparentWindow()
		{
			FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			BackColor = Color.Lime; // Set a unique color for transparency
			TransparencyKey = Color.Lime; // Make that color transparent

			closeTimer = new System.Windows.Forms.Timer();
			closeTimer.Tick += CloseTimer_Tick;

			TopMost = true; // Keep it on top
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
				return createParams;
			}
		}

		public void CloseTimer_Tick(object sender, EventArgs e)
		{
			closeTimer.Stop();
			this.Hide();
			this.Close();
		}
	}

	public class Scribbler
	{
		private TransparentWindow _window = new TransparentWindow();

		private int Thickness = 5;
		private System.Drawing.Rectangle _rect = new System.Drawing.Rectangle();
		private System.Drawing.Pen _pen = new System.Drawing.Pen(Color.Red, 3);
		

		public Scribbler()
		{
			_window.Paint += new PaintEventHandler(Paint);
		}

		//
		// P/Invoke decls
		//
		[DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true, SetLastError = true)]
		internal static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
		[DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true, SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		internal static extern bool SetWindowPos(IntPtr hWnd, IntPtr hwndAfter, int x, int y, int width, int height, int flags);

		//
		// Drawing
		//
		public void DrawRect(System.Drawing.Rectangle rectangle, System.Drawing.Color color, TimeSpan duration)
		{
			_rect = rectangle;
			//_rect = new Rectangle(50, 50, 200, 100);
			_window.closeTimer.Interval = (int)duration.TotalMilliseconds;
			_window.closeTimer.Start();

			SetWindowPos(_window.Handle, new IntPtr(-1), rectangle.X, rectangle.Y,
				rectangle.Width+5, rectangle.Height+5, SetWindowPosFlags.SWP_NOACTIVATE);
			ShowWindow(_window.Handle, ShowWindowTypes.SW_SHOWNA);

			/*Thread.Sleep(duration);
			_window.Hide();
			_window.Close();
			_window.Dispose();*/
		}

		private void Paint(object sender, PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			g.DrawRectangle(_pen, _rect);
		}
	}
}
