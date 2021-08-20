using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;
using System.Management;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace NewWorldWindowsPlugin
{
	class Import
	{
		// Windows API
		private const int SW_SHOW = 5;
		private const int SW_HIDE = 0;

		[DllImport("kernel32.dll")]
		static private extern IntPtr GetConsoleWindow();

		[DllImport("user32.dll")]
		static private extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

		[DllImport("Shell32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		static private extern void SHChangeNotify(uint wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2);

		// Actions
		static public void ShowConsole(bool show)
		{
			IntPtr handle = Import.GetConsoleWindow();

			ShowWindow(handle, show ? SW_SHOW : SW_HIDE);
		}

		static private bool isConsole = false;
		static private bool isConsoleCache = false;

		static public bool IsConsole()
		{
			if (!isConsoleCache)
			{
				try
				{
					var query = new ManagementObjectSearcher("SELECT * FROM Win32_Process WHERE ProcessId = " + Process.GetCurrentProcess().Id);

					Process parent = query.Get().OfType<ManagementObject>().Select(p => Process.GetProcessById((int)(uint)p["ParentProcessId"])).FirstOrDefault();
					isConsole = parent.ProcessName == "cmd";
				}
				catch
				{
					isConsole = false;
				}
				isConsoleCache = true;
			}

			return isConsole;
		}

		static public void UpdateRegistry()
        {
			SHChangeNotify(0x08000000, 0x0000, IntPtr.Zero, IntPtr.Zero);
		}

		static public void DeleteRegistrykey(RegistryKey root, string parentkey, string keyName)
		{
			RegistryKey reg;
			if (parentkey == null)
			{
				reg = root.OpenSubKey(keyName, false);
			}
            else
            {
				reg = root.OpenSubKey(parentkey + "\\" + keyName, false);
			}

			if (reg != null)
			{
				reg.Close();

				if (parentkey == null)
				{
					root.DeleteSubKeyTree(keyName);
				}
				else
				{
					RegistryKey parentReg = root.OpenSubKey(parentkey, true);
					parentReg.DeleteSubKeyTree(keyName);
					parentReg.Close();
				}
			}
		}
	}

	static class Program
	{
		static string Title = "New World";
		static string ApplicationName = "NewWorldPlugin";

		static string FilePath = null;
		static FileInfo FileInfo = null;

		static void ErrorMessage(string message)
		{
			if (!Import.IsConsole())
			{
				MessageBox.Show(message, Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
            else
            {
				Console.WriteLine("Error: {0}\n", message);
				HelpCommand();
			}
		}

		static void Main(string[] args)
		{
			if (!Import.IsConsole())
            {
				Application.EnableVisualStyles();
				Import.ShowConsole(false);
			}

			if (args.Length < 1 || 2 < args.Length)
			{
				ErrorMessage("This application work only on single .nwe file!");
				return;
			}

			switch (args[0])
			{
				case "--help":
					{
						HelpCommand();
						return;
					}
				case "--init-plugin":
					{
						InitPluginForWindows();
						return;
					}
			}
			

			FilePath = args[0];

			FileInfo = new FileInfo(FilePath);

			if (!Program.FileInfo.Exists)
			{
				ErrorMessage("The path \"" + FilePath + "\" does not exists!");
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

				ErrorMessage("The command \"" + args[1] + "\" does not exists!");
			}
		}

		static void HelpCommand()
		{
			Console.WriteLine("NewWorldPlugin:");
			Console.WriteLine("NewWorldPlugin --help                    - Show this help");
			Console.WriteLine("NewWorldPlugin --init-plugin             - Initialize the plugin for Windows");
			Console.WriteLine("NewWorldPlugin path                      - Open the .nwe with Visual Studio Code");
			Console.WriteLine("NewWorldPlugin path --help               - Show this help");
			Console.WriteLine("NewWorldPlugin path --generate-projects  - Generate Projects");
			Console.WriteLine("NewWorldPlugin path --build              - Build the applications");
		}

		static void InitPluginForWindows()
		{
			try
			{
				// Remove lass Registry data
				try
				{
					Import.DeleteRegistrykey(Registry.ClassesRoot, null, ".nwe");
					Import.DeleteRegistrykey(Registry.ClassesRoot, null, ApplicationName);
				}
				catch { }

				Import.UpdateRegistry();

				// Get Application Path
				string applicationPath = Application.ExecutablePath;

				// Get Logo.ico path
				string applicationFolder = Application.StartupPath;
				DirectoryInfo directory = new DirectoryInfo(applicationFolder);

				string logoPath = directory.Parent.Parent.FullName + "\\Logo.ico";

				// Create Keys
				RegistryKey fileReg = Registry.ClassesRoot.CreateSubKey(@".nwe");
				RegistryKey appReg = Registry.ClassesRoot.CreateSubKey(ApplicationName);

				fileReg.SetValue("", ApplicationName);
				fileReg.SetValue("Content Type", "application/json");
				fileReg.CreateSubKey("OpenWithList\\" + ApplicationName).SetValue("", "");
				fileReg.CreateSubKey("OpenWithProgids").SetValue(ApplicationName, 0);
				fileReg.CreateSubKey("PerceivedType").SetValue("", "Text");

				appReg.SetValue("", "New World Engine");
				appReg.CreateSubKey("DefualtIcon").SetValue("", logoPath);
				appReg.CreateSubKey(@"shell\open\command").SetValue("", "\"" + applicationPath + "\" %1");

				fileReg.Close();
				appReg.Close();

				Import.UpdateRegistry();
			}
			catch (Exception ex)
			{
				ErrorMessage(ex.Message);
			}

			Import.UpdateRegistry();
		}

		static void OpenWith()
		{
			try
			{
				string codePath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
				codePath = codePath.Remove(codePath.Length - 8, 8);
				codePath += "\\Local\\Programs\\Microsoft VS Code\\Code.exe";

				if (!File.Exists(codePath))
                {
					ErrorMessage("Visual Studio Code does not installed!");
					return;
				}

				var p = Process.Start(codePath, FilePath);
				Environment.Exit(0);
			}
			catch
			{
				ErrorMessage("Can't open Visual Studio Code!");
			}
		}

		static void GenerateProjectsCommand()
		{

		}

		static void BuildCommand()
		{

		}
	}
}
