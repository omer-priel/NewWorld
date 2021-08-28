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
			Console.WriteLine("");
			Console.WriteLine("NewWorldPlugin [option] path");
			Console.WriteLine("\tpath                     - Open the.nwe with Visual Studio Code");
			Console.WriteLine("\t--help                   - Show this help");
			Console.WriteLine("\t--install-extension      - Install the extension");
			Console.WriteLine("\t--uninstall-extension    - Uninstall the extension");
			Console.WriteLine("\t--generate-projects path - Generate Projects");
			Console.WriteLine("\t--build path             - Build the applications");
		}

		static public void InstallExtension()
		{
			UninstallExtension();

			try
			{
				// Get Application Folder
				string applicationFolder = Application.StartupPath;

				// Add Application Folder to Windows PATH
				string pathVariable = Environment.GetEnvironmentVariable("PATH", EnvironmentVariableTarget.Machine);

				if (Array.IndexOf(pathVariable.Split(';'), applicationFolder) == -1)
				{
					pathVariable += ";" + applicationFolder;
					Environment.SetEnvironmentVariable("PATH", pathVariable, EnvironmentVariableTarget.Machine);
				}

				// Get Logo.ico path
				DirectoryInfo directory = new DirectoryInfo(applicationFolder);

				string pluginPath = "\"" + Application.ExecutablePath + "\"";
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
				appReg.CreateSubKey(@"shell\open\command").SetValue("", pluginPath + " %1");

				RegistryKey buildReg = appReg.CreateSubKey(@"shell\Build");
				buildReg.SetValue("", "Build");
				buildReg.SetValue("Icon", logoPath);
				buildReg.CreateSubKey("command").SetValue("", pluginPath + " --build %1");
				buildReg.Close();

				RegistryKey generateProjectsReg = appReg.CreateSubKey(@"shell\GenerateProjects");
				generateProjectsReg.SetValue("", "Generate Projects");
				generateProjectsReg.SetValue("Icon", logoPath);
				generateProjectsReg.CreateSubKey("command").SetValue("", pluginPath + " --generate-projects %1");
				generateProjectsReg.Close();

				fileReg.Close();
				appReg.Close();

				WindowsAPI.UpdateRegistry();
			}
			catch (Exception ex)
			{
				Utilities.ShowErrorMessage(ex.Message);
			}

			WindowsAPI.UpdateRegistry();
		}

		static public void UninstallExtension()
		{
			try
			{
				// Get Application Folder
				string applicationFolder = Application.StartupPath;

				// Remove Application Folder to Windows PATH
				string pathVariable = Environment.GetEnvironmentVariable("PATH", EnvironmentVariableTarget.Machine);

				List<string> list = pathVariable.Split(';').ToList();
				list.Remove(applicationFolder);

				pathVariable = "";
				foreach (string path in list)
				{
					pathVariable += path + ";";
				}

				Environment.SetEnvironmentVariable("PATH", pathVariable, EnvironmentVariableTarget.Machine);
			}
			catch { }

			try
			{
				// Remove plugin from the Registry
				WindowsAPI.DeleteRegistrykey(Registry.ClassesRoot, null, ".nwe");
				WindowsAPI.DeleteRegistrykey(Registry.ClassesRoot, null, Plugin.ApplicationName);
			}
			catch { }

			WindowsAPI.UpdateRegistry();
		}

		static public void GenerateProjects()
		{
			Utilities.CallDevOpsScript("GenerateProjects");
		}

		static public void Build()
		{
			Utilities.CallDevOpsScript("Build");
		}
	}
}
