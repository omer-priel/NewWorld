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
			
			if (args.Length == 0)
			{
				Utilities.ErrorMessage("See NewWorldPlugin --help");
				return;
			}

			switch (args[0])
			{
				case "--help":
					{
						Commands.Help();
						return;
					}
				case "--install-extension":
					{
						Commands.InstallExtension();
						return;
					}
                case "--uninstall-extension":
					{
						Commands.UninstallExtension();
						return;
					}
				case "--generate-projects":
					{
						if (args.Length < 2)
						{
							Utilities.ErrorMessage("The path of the file is missing!");
						}
						else if (Plugin.LoadNWEFile(args[1]))
						{
							Commands.GenerateProjects();
						}
						return;
					}
				case "--build":
					{
						if (args.Length < 2)
						{
							Utilities.ErrorMessage("The path of the file is missing!");
						}
						else if (Plugin.LoadNWEFile(args[1]))
						{
							Commands.Build();
						}
						return;
					}
			}

			// open .nwe file
			if (!Plugin.LoadNWEFile(args[0]))
			{
				return;
			}
			else
			{
				OpenWith();
			}
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
					Utilities.ErrorMessage("Visual Studio Code does not installed!");
					return;
				}

				Process.Start(codePath, Plugin.NewWorldFile.Directory.FullName);
				Environment.Exit(0);
			}
			catch
			{
				Utilities.ErrorMessage("Can't open Visual Studio Code!");
			}
		}
	}
}
