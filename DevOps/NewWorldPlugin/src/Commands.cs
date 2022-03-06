using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Microsoft.Win32;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace NewWorldPlugin
{
	static public class Commands
	{
		static public void Help()
		{	
			Console.WriteLine("NewWorldPlugin [options]      - Open in Visual Studio Code");
			Console.WriteLine("NewWorldPlugin [options] [command]");
			Console.WriteLine("Commands:");
			Console.WriteLine("\t" + "help                   - Show this help");
			Console.WriteLine("\t" + "install-extension      - Install the extension");
			Console.WriteLine("\t" + "uninstall-extension    - Uninstall the extension");
			Console.WriteLine("\t" + "generate-projects      - Generate Projects");
			Console.WriteLine("\t" + "build                  - Build the applications");
			Console.WriteLine("\t" + "create-font [path]     - Create .nwf from .json");
			Console.WriteLine("\t" + "create-shader [path]   - Create .nws from .shader");
			Console.WriteLine("Options:");
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
				RegistryKey fontFileReg = Registry.ClassesRoot.CreateSubKey(@".nwf");

				RegistryKey appReg = Registry.ClassesRoot.CreateSubKey(Plugin.ApplicationName);

				fileReg.SetValue("", Plugin.ApplicationName);
				fileReg.SetValue("Content Type", "application/json");
				fileReg.CreateSubKey("OpenWithList\\" + Plugin.ApplicationName).SetValue("", "");
				fileReg.CreateSubKey("OpenWithProgids").SetValue(Plugin.ApplicationName, 0);
				fileReg.CreateSubKey("PerceivedType").SetValue("", "Text");

				fontFileReg.SetValue("", "New World Font");
				fontFileReg.SetValue("Content Type", "application/nwf");

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
				fontFileReg.Close();

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
			FileInfo fileInfo = LoadSrcPath(path, ".json");
			if (fileInfo == null)
			{
				return;
			}

			string folder = fileInfo.DirectoryName;
			string fileName = fileInfo.Name.Replace(fileInfo.Extension, "");
			string targetPath = folder + "\\" + fileName + ".nwf";

			// Load the File
			string json = File.ReadAllText(path);

			dynamic data = JsonConvert.DeserializeObject(json);

			string familyName;
			uint size;
			bool bold;
			bool italic;
			uint width;
			uint height;
			JObject characters;

			try
			{
				familyName = data.name;
				size = data.size;
				bold = data.bold;
				italic = data.italic;
				width = data.width;
				height = data.height;

				characters = data.characters;
			}
			catch
			{
				Utilities.ShowErrorMessage("The font is damaged!");
				return;
			}

			// Create .nwf file
			BinaryWriter writer = new BinaryWriter(new FileStream(targetPath, FileMode.Create));
			
			writer.Write(familyName.Length); // FamilyNameLength
			writer.Write(familyName.ToArray(), 0, familyName.Length); // FamilyName

			writer.Write(size);
			writer.Write(bold);
			writer.Write(italic);
			writer.Write(width);
			writer.Write(height);

			writer.Write(characters.Count); // CharactersCount

			foreach (JProperty character in characters.Children())
			{
				dynamic value = character.Value;
				writer.Write(character.Name[0]); // Name
				writer.Write((int)value.x); // AtlasX
				writer.Write((int)value.y); // AtlasY
				writer.Write((int)value.width); // Width
				writer.Write((int)value.height); // Height
				writer.Write((int)value.originX); // OriginX
				writer.Write((int)value.originY); // OriginY
				writer.Write((int)value.advance); // PainterStepX
			}

			writer.Close();
		}

		static public void CreateShader(string path)
        {
			FileInfo fileInfo = LoadSrcPath(path, ".shader");
			if (fileInfo == null)
            {
				return;
            }

			string folder = fileInfo.DirectoryName;
			string fileName = fileInfo.Name.Replace(fileInfo.Extension, "");
			string targetPath = folder + "\\" + fileName + ".nws";

			// Load the File
			string[] shaderPartTypes = {
				"#shader vertex",
				"#shader geometry",
				"#shader fragment"
			};

			string[] shaderParts = new string[shaderPartTypes.Length];
            for (int i = 0; i < shaderParts.Length; i++)
            {
				shaderParts[i] = "";
			}

			int index = -1;

			TextReader reader = File.OpenText(path);

			string line;
			while ((line = reader.ReadLine()) != null)
            {
				if (line.StartsWith("#shader"))
                {
					index = -1;
					for (int i = 0; i < shaderPartTypes.Length && index == -1; i++)
                    {
						if (line.StartsWith(shaderPartTypes[i]))
                        {
							index = i;
                        }
                    }
                }
				else if (index != -1 && line.Length > 0)
                {
					if (shaderParts[index].Length == 0)
					{
						shaderParts[index] = line;
					}
					else
					{
						shaderParts[index] += "\n" + line;
					}
                }
            }

			// Create the .nws file
			BinaryWriter writer = new BinaryWriter(new FileStream(targetPath, FileMode.Create));

            foreach (var shaderPart in shaderParts)
            {
				writer.Write(shaderPart.Length);
				writer.Write(shaderPart.ToArray(), 0, shaderPart.Length);
			}
		}

		// Utilities
		static FileInfo LoadSrcPath(string path, string needExtension)
        {
			if (!File.Exists(path))
			{
				Utilities.ShowErrorMessage("The file \"" + path + "\" not exists!");
				return null;
			}

			FileInfo fileInfo = new FileInfo(path);
			if (fileInfo.Extension != needExtension)
			{
				Utilities.ShowErrorMessage("Is not " + needExtension + " file!");
				return null;
			}

			return fileInfo;
		}
	}
}
