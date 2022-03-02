using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using Microsoft.Win32;

namespace NewWorldPlugin
{
	static class Program
	{
		static void Main(string[] args)
		{
			Plugin.Init();

			string rootPath = Directory.GetCurrentDirectory();

			int index = 0;
			while (index < args.Length && args[index].StartsWith("--"))
            {
				string option = args[index];
				switch (option)
				{
					case "--root-path":
						{
							index++;
							if (index == args.Length)
                            {
								Utilities.ShowErrorMessage("Need path as parment!");
								return;
							}

							rootPath = args[index];

							if (File.Exists(rootPath) && rootPath.EndsWith(".nwe"))
                            {
								rootPath = new FileInfo(rootPath).DirectoryName;

							}

							if (!Directory.Exists(rootPath))
                            {
								Utilities.ShowErrorMessage("The path \"" + rootPath + "\" does not exists!");
								return;
							}
						}
						break;
					default:
                        {
							Utilities.ShowErrorMessage("The option \"" + option + "\" does not exists!");
							return;
                        }
				}
				index++;
            }

			if (index == args.Length)
			{
				if (!Plugin.LoadNWEFile(rootPath))
				{
					return;
				}
				else
				{
					OpenWith();
				}
			}

			string command = args[index];

			switch (command)
			{
				case "help":
					{
						Commands.Help();
						return;
					}
				case "install-extension":
					{
						Commands.InstallExtension();
						return;
					}
                case "uninstall-extension":
					{
						Commands.UninstallExtension();
						return;
					}
				case "generate-projects":
					{
						if (Plugin.LoadNWEFile(rootPath))
						{
							Commands.GenerateProjects();
						}
						return;
					}
				case "build":
					{
						if (Plugin.LoadNWEFile(rootPath))
						{
							Commands.Build();
						}
						return;
					}
			}
		}

		// Open .nwe file
		static void OpenWith()
		{
			try
			{
				// get VSCode pathh
				string codePath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
				codePath = codePath.Remove(codePath.Length - 8, 8);
				codePath += "\\Local\\Programs\\Microsoft VS Code\\Code.exe";

				if (!File.Exists(codePath))
                {
					Utilities.ShowErrorMessage("Visual Studio Code does not installed!");
					return;
				}

				// open New World Solution Folder with Vscode
				Process.Start(codePath, Plugin.NewWorldFile.Directory.FullName);
				Environment.Exit(0);
			}
			catch
			{
				Utilities.ShowErrorMessage("Can't open Visual Studio Code!");
			}
		}
	}
}
