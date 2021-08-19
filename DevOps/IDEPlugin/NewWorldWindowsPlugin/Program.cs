using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;

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

		static void ErrorMessage(string message)
		{
			Imoprt.ShowConsole(false);

			MessageBox.Show(message, Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		static void Main(string[] args)
		{
			Application.EnableVisualStyles();
			Imoprt.ShowConsole(false);

			if (args.Length < 1 || 2 < args.Length)
			{
				ErrorMessage("This application work only on single .nwe file!");
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
				ErrorMessage("The path " + FilePath + " does not exists!");
				return;
			}

			if (Program.FileInfo.Extension != ".nwe")
			{
				ErrorMessage("This application work only on single .nwe file!");
				return;
			}

			if (args.Length == 1)
			{
				OpenWith();
			}
			else
			{
				switch (args[1]) // commands
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

				Imoprt.ShowConsole(true);
				Console.WriteLine("Error: The command \"{0}\" does not exists!", args[0]);
				HelpCommand();
			}
		}

		static void HelpCommand()
		{
			Imoprt.ShowConsole(true);

			Console.WriteLine("NewWorldPlugin:");
			Console.WriteLine("{0} - Open the .nwe with Visual Studio Code");
			Console.WriteLine("NewWorldPlugin --help                    - Show this help");
			Console.WriteLine("NewWorldPlugin path                      - Open the .nwe with Visual Studio Code");
			Console.WriteLine("NewWorldPlugin path --help               - Show this help");
			Console.WriteLine("NewWorldPlugin path --generate-projects  - Generate Projects");
			Console.WriteLine("NewWorldPlugin path --build              - Build the applications");
		}

		static void OpenWith()
		{
			Process.Start("code", FilePath);
		}

		static void GenerateProjectsCommand()
		{

		}

		static void BuildCommand()
		{

		}
	}
}
