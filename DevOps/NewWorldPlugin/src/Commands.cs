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
			Console.WriteLine("NewWorldPlugin [options]    - Open in Visual Studio Code");
			Console.WriteLine("NewWorldPlugin [options] [command]");
			Console.WriteLine("Commands:");
			Console.WriteLine("\t" + "help                   - Show this help");
			Console.WriteLine("\t" + "install-extension      - Install the extension");
			Console.WriteLine("\t" + "uninstall-extension    - Uninstall the extension");
			Console.WriteLine("\t" + "generate-projects      - Generate Projects");
			Console.WriteLine("\t" + "build                  - Build the applications");
			Console.WriteLine("\t" + "create-font path       - Create .nwf from .json");
			Console.WriteLine("Options");
			Console.WriteLine("\t" + "--root-path [path]     - Change the nwe directory to use");
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
				appReg.CreateSubKey(@"shell\open\command").SetValue("", pluginPath + " --root-path %1");

				RegistryKey buildReg = appReg.CreateSubKey(@"shell\Build");
				buildReg.SetValue("", "Build");
				buildReg.SetValue("Icon", logoPath);
				buildReg.CreateSubKey("command").SetValue("", pluginPath + " --root-path %1 build");
				buildReg.Close();

				RegistryKey generateProjectsReg = appReg.CreateSubKey(@"shell\GenerateProjects");
				generateProjectsReg.SetValue("", "Generate Projects");
				generateProjectsReg.SetValue("Icon", logoPath);
				generateProjectsReg.CreateSubKey("command").SetValue("", pluginPath + " --root-path %1 generate-projects");
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

		static public void CreateFont(string path)
		{
			if (!File.Exists(path))
			{
				Utilities.ShowErrorMessage("The file \"" + path + "\" not exists!");
				return;
			}

			FileInfo fileInfo = new FileInfo(path);
			if (fileInfo.Extension.ToLower() != ".json")
			{
				Utilities.ShowErrorMessage("Is not .json file!");
				return;
			}

			System.Console.WriteLine(File.ReadAllText(path));
		}
	}
}
