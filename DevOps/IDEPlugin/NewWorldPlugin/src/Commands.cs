using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Microsoft.Win32;

namespace NewWorldPlugin
{
	static public class Commands
	{
		static public void Help()
		{
			Console.WriteLine("NewWorldPlugin:");
			Console.WriteLine("NewWorldPlugin path                      - Open the .nwe with Visual Studio Code");
			Console.WriteLine("NewWorldPlugin --help                    - Show this help");
			Console.WriteLine("NewWorldPlugin --install-extension       - Install the extension");
			Console.WriteLine("NewWorldPlugin --uninstall-extension     - Uninstall the extension");
			Console.WriteLine("NewWorldPlugin --generate-projects path  - Generate Projects");
			Console.WriteLine("NewWorldPlugin --build path              - Build the applications");
		}

		static public void InstallExtension()
		{
			UninstallExtension();

			try
			{
				// Get Application Path
				string applicationPath = Application.ExecutablePath;

				// Get Logo.ico path
				string applicationFolder = Application.StartupPath;
				DirectoryInfo directory = new DirectoryInfo(applicationFolder);

				string logoPath = directory.Parent.Parent.FullName + "\\Logo.ico";

				// Create Keys
				RegistryKey fileReg = Registry.ClassesRoot.CreateSubKey(@".nwe");
				RegistryKey appReg = Registry.ClassesRoot.CreateSubKey(Plugin.ApplicationName);

				fileReg.SetValue("", Plugin.ApplicationName);
				fileReg.SetValue("Content Type", "application/json");
				fileReg.CreateSubKey("OpenWithList\\" + Plugin.ApplicationName).SetValue("", "");
				fileReg.CreateSubKey("OpenWithProgids").SetValue(Plugin.ApplicationName, 0);
				fileReg.CreateSubKey("PerceivedType").SetValue("", "Text");

				appReg.SetValue("", "New World Engine");
				appReg.CreateSubKey("DefualtIcon").SetValue("", logoPath);
				appReg.CreateSubKey(@"shell\open\command").SetValue("", "\"" + applicationPath + "\" %1");

				RegistryKey buildReg = appReg.CreateSubKey(@"shell\Build");
				buildReg.SetValue("", "Build");
				buildReg.SetValue("Icon", logoPath);
				buildReg.CreateSubKey("command").SetValue("", "\"" + applicationPath + "\" --build %1");
				buildReg.Close();

				RegistryKey generateProjectsReg = appReg.CreateSubKey(@"shell\GenerateProjects");
				generateProjectsReg.SetValue("", "Generate Projects");
				generateProjectsReg.SetValue("Icon", logoPath);
				generateProjectsReg.CreateSubKey("command").SetValue("", "\"" + applicationPath + "\" --generate-projects %1");
				generateProjectsReg.Close();

				fileReg.Close();
				appReg.Close();

				WindowsAPI.UpdateRegistry();
			}
			catch (Exception ex)
			{
				Utilities.ErrorMessage(ex.Message);
			}

			WindowsAPI.UpdateRegistry();
		}

		static public void UninstallExtension()
		{
			// Remove lass Registry data
			try
			{
				WindowsAPI.DeleteRegistrykey(Registry.ClassesRoot, null, ".nwe");
				WindowsAPI.DeleteRegistrykey(Registry.ClassesRoot, null, Plugin.ApplicationName);
			}
			catch { }

			WindowsAPI.UpdateRegistry();
		}

		static public void GenerateProjects()
		{
			Utilities.StartDevOpsScript("GenerateProjects");
		}

		static public void Build()
		{
			Utilities.StartDevOpsScript("Build");
		}
	}
}
