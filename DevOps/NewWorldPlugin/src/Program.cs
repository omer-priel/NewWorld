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

			CallCommand(args);
		}

		static void CallCommand(string[] args)
        {
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
								Utilities.ShowErrorMessage("Need path as parament!");
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
				if (!Plugin.LoadProject(rootPath))
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
					}
					break;
				case "install-extension":
					{
						Commands.InstallExtension();
					}
					break;
				case "uninstall-extension":
					{
						Commands.UninstallExtension();
					}
					break;
				case "generate-projects":
					{
						if (Plugin.LoadProject(rootPath))
						{
							Commands.GenerateProjects();
						}
					}
					break;
				case "build":
					{
						if (Plugin.LoadProject(rootPath))
						{
							Commands.Build();
						}
					}
					break;
				case "create-font":
					{
						index++;
						if (index == args.Length)
						{
							Utilities.ShowErrorMessage("Need path as parament!");
							return;
						}

						string path = args[index];
						Commands.CreateFont(path);
					}
					break;
				case "shader":
					{
						index++;
						if (index == args.Length)
						{
							Utilities.ShowErrorMessage("Need sub command!");
							return;
						}

						command = args[index];
						switch (command)
						{
							case "create":
								{
									index++;
									if (index == args.Length)
									{
										Utilities.ShowErrorMessage("Need path as parament!");
										return;
									}

									string path = args[index];
									Commands.CreateShader(path);
								}
								break;
							case "create-all":
								{
									if (Plugin.LoadProject(rootPath))
									{
										Commands.CreateAllShaders();
									}
								}
								break;
							default:
								{
									Utilities.ShowErrorMessage("The command \"shader " + command + "\" dos not exists!");
								}
								return;
						}
					}
					break;
				default:
					{
						Utilities.ShowErrorMessage("The command \"" + command + "\" dos not exists!");
					}
					return;
			}
		}

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
