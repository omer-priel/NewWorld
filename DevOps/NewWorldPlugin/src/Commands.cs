using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Drawing;

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

			Image[] textures = new Image[textureFilesPaths.Length];

			string targetDataPath = path + ".nwf";
			string targetTexturePath = path + ".nwf.png";

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

			if (File.Exists(targetDataPath))
            {
				File.Delete(targetDataPath);
            }

			if (File.Exists(targetTexturePath))
			{
				File.Delete(targetTexturePath);
			}

			// Create the Font
			BinaryWriter writer = new BinaryWriter(new FileStream(targetDataPath, FileMode.Create));

			// Load general data
			Size textureStyleSize = new Size(0, 0);

			for (int i = 0; i < textures.Length; i++)
			{
				string texturePath = textureFilesPaths[i];

				if (File.Exists(texturePath))
				{
					textures[i] = Image.FromFile(textureFilesPaths[i]);

					if (textureStyleSize.Width < textures[i].Width)
                    {
						textureStyleSize.Width = textures[i].Width;
					}

					if (textureStyleSize.Height < textures[i].Height)
					{
						textureStyleSize.Height = textures[i].Height;
					}
				}
				else
                {
					textures[i] = null;
				}
			}

			Bitmap fontTexture = new Bitmap(textureStyleSize.Width * 2, textureStyleSize.Height * 2);
			Graphics graphics = Graphics.FromImage(fontTexture);

			graphics.FillRectangle(Brushes.Transparent, 0, 0, fontTexture.Width, fontTexture.Height);

			graphics.Dispose();

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
			bool success = true;
			for (int i = 0; i < dataFilesPaths.Length && success; i++)
			{
				string dataPath = dataFilesPaths[i];
				Image texture = textures[i];

				if (!File.Exists(dataPath) || texture == null)
				{
					dataPath = dataFilesPaths[0];
					texture = textures[0];
				}

				success = AddFontStyleToFont(writer, fontTexture, textureStyleSize, i, dataPath, texture);
			}

			// Save the Files
			writer.Close();

			fontTexture.Save(targetTexturePath, System.Drawing.Imaging.ImageFormat.Png);
			fontTexture.Dispose();
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

		// Hellpers
		// Create Font Hellpers
		static private bool AddFontStyleToFont(BinaryWriter writer, Bitmap fontTexture, Size textureStyleSize, int styleID, string dataPath, Image texture)
		{
			bool bold = (styleID % 2) == 1;
			bool italic = ((styleID % 4) / 2) == 1;

			// Load the Data File
			string json = File.ReadAllText(dataPath);

			dynamic data = JsonConvert.DeserializeObject(json);

			JObject characters;

			try
			{
				characters = data.characters;
			}
			catch
			{
				Utilities.ShowErrorMessage("The font is damaged!");
				return false;
			}

			// Append the to the texture
			int xStart = 0;
			int yStart = 0;

			if (bold)
			{
				xStart += textureStyleSize.Width;
			}

			if (italic)
			{
				yStart += textureStyleSize.Height;
			}

			Graphics graphics = Graphics.FromImage(fontTexture);
			graphics.DrawImage(texture, xStart, yStart);

			graphics.Dispose();

			// Append to .nwf
			foreach (JProperty character in characters.Children())
			{
				dynamic value = character.Value;
				writer.Write(character.Name[0]); // Name

				short atlasX = (short)(xStart + (short)value.x);
				short atlasY = (short)(yStart + (short)value.y);

				atlasY = (short)(fontTexture.Height - atlasY - (short)value.height); // flip y

				writer.Write(atlasX); // AtlasX
				writer.Write(atlasY); // AtlasY

				writer.Write((short)value.width); // Width
				writer.Write((short)value.height); // Height

				short originX = (short)value.originX;
				short originY = (short)value.originY;

				originX *= -1;
				originY -= (short)value.height; // flip y

				writer.Write(originX); // OriginX
				writer.Write(originY); // OriginY
				
				writer.Write((short)value.advance); // PainterStepX
			}

			return true;
		}

		// Create Shader Hellpers
		static private void CreateShaderFromFile(FileInfo fileInfo)
		{
			string folder = fileInfo.DirectoryName;
			string fileName = fileInfo.Name.Replace(fileInfo.Extension, "");
			string targetPath = folder + "\\" + fileName + ".nws";

			// Load the File
			string[] generalPartTypes = {
				"#header",
			};

			string[] shaderPartTypes = {
				"#shader vertex",
				"#shader geometry",
				"#shader fragment"
			};

			string[] parts = new string[generalPartTypes.Length + shaderPartTypes.Length];
			for (int i = 0; i < parts.Length; i++)
			{
				parts[i] = "";
			}

			int index = -1;

			TextReader reader = File.OpenText(fileInfo.FullName);

			string line;
			while ((line = reader.ReadLine()) != null)
			{
				if (line.StartsWith("#shader") || line.StartsWith("#header"))
				{
					index = -1;
					for (int i = 0; i < generalPartTypes.Length && index == -1; i++)
					{
						if (line.StartsWith(generalPartTypes[i]))
						{
							index = i;
						}
					}

					for (int i = 0; i < shaderPartTypes.Length && index == -1; i++)
					{
						if (line.StartsWith(shaderPartTypes[i]))
						{
							index = generalPartTypes.Length + i;
						}
					}
				}
				else if (index != -1 && line.Length > 0)
				{
					while (line.Contains("//"))
					{
						line = line.Substring(0, line.IndexOf("//"));
					}
					if (line.Replace(" ", "").Replace("\t", "").Length > 0)
					{
						if (parts[index].Length == 0)
						{
							parts[index] = line;
						}
						else
						{
							parts[index] += "\n" + line;
						}
					}
				}
			}

			// Create the .nws file
			BinaryWriter writer = new BinaryWriter(new FileStream(targetPath, FileMode.Create));

			string header = parts[0];

			for (int i = generalPartTypes.Length; i < parts.Length; i++)
			{
				string shaderPart = parts[i];

				if (header.Length > 0 && shaderPart.Length > 0)
				{
					shaderPart = header + "\n" + shaderPart;
				}

				writer.Write(shaderPart.Length);
				writer.Write(shaderPart.ToArray(), 0, shaderPart.Length);
			}
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
