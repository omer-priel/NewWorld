using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO;

namespace NewWorldWindowsPlugin
{
	class Imoprt
	{
		private const int SW_SHOW = 5;
		private const int SW_HIDE = 0;

		[DllImport("kernel32.dll")]
		static private extern IntPtr GetConsoleWindow();

		[DllImport("user32.dll")]
		static private extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

		// Actions
		static public void ShowConsole(bool show)
		{
			IntPtr handle = Imoprt.GetConsoleWindow();

			ShowWindow(handle, show ? SW_SHOW : SW_HIDE);
		}
	}

	static class Program
	{
		static string Title = "New World";

		static string FilePath = null;
		static FileInfo FileInfo = null;

		static void Main(string[] args)
		{
			Application.EnableVisualStyles();

			if (1 <= args.Length && args.Length <= 2)
			{
				Imoprt.ShowConsole(false);

				MessageBox.Show("This application work only on single .nwe file!", Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			if (args[0] == "--help")
			{
				HelpCommand();
				return;
			}

			FilePath = args[0];

			FileInfo = new FileInfo(FilePath);

			if (!Program.FileInfo.Exists)
			{
				MessageBox.Show("The path " + FilePath + " does not exists!", Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			if (Program.FileInfo.Extension != ".nwe")
			{
				MessageBox.Show("This application work only on single .nwe file!", Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			if (args.Length == 1)
			{
				OpenWith();
			}
			else
			{
				switch (args[1])
				{
					case "--help":
						{
							HelpCommand();
							return;
						}
					case "--generate-projects":
						{
							GenerateProjectsCommand();
							return;
						}
					case "--build":
						{
							BuildCommand();
							return;
						}
				}

				Console.WriteLine("Error: The command {0} does not exists!", args[0]);
				HelpCommand();
			}
		}

		static void HelpCommand()
		{
			Console.WriteLine("");

			Console.Write("Press any key to continue . . . ");
			Console.ReadKey();
		}

		static void OpenWith()
		{

		}

		static void GenerateProjectsCommand()
		{

		}

		static void BuildCommand()
		{

		}
	}
}
