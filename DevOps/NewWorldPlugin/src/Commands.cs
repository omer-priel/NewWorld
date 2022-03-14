﻿using System;
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
			Console.WriteLine("\t" + "help                     - Show this help");
			Console.WriteLine("\t" + "install-extension        - Install the extension");
			Console.WriteLine("\t" + "uninstall-extension      - Uninstall the extension");
			Console.WriteLine("\t" + "generate-projects        - Generate Projects");
			Console.WriteLine("\t" + "build                    - Build the applications");
			Console.WriteLine("\t" + "create-font [path]       - Create .nwf");
			Console.WriteLine("\t" + "shader create [path]     - Create .nws from .shader");
			Console.WriteLine("\t" + "shader create-all        - Create all the shaders");
			Console.WriteLine("\t" + "pre-compile [target]     - Pre Compile Processing");
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
			string[] dataFilesPaths = { path + ".json", path + "Bold.json", path + "Iltalic.json", path + "BoldIltalic.json" };
			string[] textureFilesPaths = { path + ".png", path + "Bold.png", path + "Iltalic.png", path + "BoldIltalic.png" };
			string targetPath = path + ".nwf";

			if (!File.Exists(dataFilesPaths[0]))
			{
				Utilities.ShowErrorMessage("The file \"" + dataFilesPaths[0] + "\" not exists!");
				return;
			}

			if (!File.Exists(textureFilesPaths[0]))
			{
				Utilities.ShowErrorMessage("The file \"" + textureFilesPaths[0] + "\" not exists!");
				return;
			}

			// Create the Font
			BinaryWriter writer = new BinaryWriter(new FileStream(targetPath, FileMode.Create));

			// create header
			string json = File.ReadAllText(dataFilesPaths[0]);

			dynamic data = JsonConvert.DeserializeObject(json);

			string familyName;
			uint size;
			JObject characters;

			try
			{
				familyName = data.name;
				size = data.size;
				characters = data.characters;
			}
			catch
			{
				Utilities.ShowErrorMessage("The font is damaged!");
				return;
			}

			byte[] familyNameAsBytes = Encoding.ASCII.GetBytes(familyName);

			writer.Write(familyNameAsBytes.Length); // FamilyNameLength
			writer.Write(familyNameAsBytes, 0, familyNameAsBytes.Length); // FamilyName

			writer.Write(size);
			writer.Write(characters.Count); // CharactersCount

			// crate the body
			for (int i = 0; i < dataFilesPaths.Length; i++)
			{
				string dataPath = dataFilesPaths[i];
				string texturePath = textureFilesPaths[i];

				if (!File.Exists(dataPath) || !File.Exists(texturePath))
				{
					dataPath = dataFilesPaths[0];
					texturePath = textureFilesPaths[0];
				}

				// Load the Data File
				json = File.ReadAllText(dataPath);

				data = JsonConvert.DeserializeObject(json);

				try
				{
					characters = data.characters;
				}
				catch
				{
					Utilities.ShowErrorMessage("The font is damaged!");
					return;
				}

				// Append to .nwf
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

				// Append the to the texture

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

			CreateShaderFromFile(fileInfo);
		}

		static public void CreateAllShaders()
		{
			string folderPath = Plugin.GetPath(@"Assets");

			DirectoryInfo directoryInfo = new DirectoryInfo(folderPath);
			FileInfo[] files = directoryInfo.GetFiles("**.shader", SearchOption.AllDirectories);

			foreach (FileInfo file in files)
			{
				CreateShaderFromFile(file);
			}
		}

		static public void PreCompile(string target)
		{
			string assetsPath = Plugin.GetPath(@"Assets");

			if (!Directory.Exists(target))
			{
				target = Plugin.GetPath(target);
			}

			DeleteDirectory(target + "\\assets");
			CopyDirectory(assetsPath, target + "\\assets");
		}

		// Utilities
		static private FileInfo LoadSrcPath(string path, string needExtension)
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

		static private void CreateShaderFromFile(FileInfo fileInfo)
		{
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

			TextReader reader = File.OpenText(fileInfo.FullName);

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

		static private void DeleteDirectory(string directoryPath)
		{
			if (Directory.Exists(directoryPath))
			{
				// Delete the files
				foreach (string path in Directory.GetFiles(directoryPath))
				{
					File.Delete(path);
				}

				// Delete the directories
				foreach (string path in Directory.GetDirectories(directoryPath))
				{
					DeleteDirectory(path);
				}

				Directory.Delete(directoryPath);
			}
		}

		static private void CopyDirectory(string sourcePath, string targetPath)
		{
			Directory.CreateDirectory(targetPath);

			// Create all of the directories
			foreach (string path in Directory.GetDirectories(sourcePath, "*", SearchOption.AllDirectories))
			{
				Directory.CreateDirectory(path.Replace(sourcePath, targetPath));
			}

			// Copy all the files
			foreach (string path in Directory.GetFiles(sourcePath, "*.*", SearchOption.AllDirectories))
			{
				File.Copy(path, path.Replace(sourcePath, targetPath), true);
			}
		}
	}
}
