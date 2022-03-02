using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace NewWorldPlugin
{
	static public class Plugin
	{
		// Plugin settings
		static public string Title = "New World";
		static public string ApplicationName = "NewWorldPlugin";

		// .nwe file info
		static public DirectoryInfo NewWorldRootDirectory = null;
		static public FileInfo NewWorldFile = null;

		// Initialize the Plugin
		static public void Init()
		{
			if (!WindowsAPI.IsConsole())
			{
				Application.EnableVisualStyles();
				WindowsAPI.ShowConsole(false);
			}
		}

		// Get subpath of the solution
		static public string GetPath(string subpath)
		{
			return NewWorldRootDirectory.FullName + "\\" + subpath;
		}

		// Load .nwe file
		static public bool LoadNWEFile()
		{
			DirectoryInfo rootDirectory = new DirectoryInfo(Directory.GetCurrentDirectory());
			NewWorldFile = null;

			while (NewWorldFile == null)
            {
				FileInfo[] nwes = rootDirectory.GetFiles("*.nwe");
				if (nwes.Length > 0)
                {
					NewWorldRootDirectory = rootDirectory;
					NewWorldFile = nwes[0];
				}

				if (rootDirectory.Parent == null)
                {
					Utilities.ShowErrorMessage("Thw .new does not exists!");
					return false;
				}

				rootDirectory = rootDirectory.Parent;

			}

			if (!NewWorldFile.Exists)
			{
				//Utilities.ShowErrorMessage("The path \"" + nweFilePath + "\" does not exists!");
				return false;
			}

			if (NewWorldFile.Extension != ".nwe")
			{
				Utilities.ShowErrorMessage("This file is not a .nwe file!");
				return false;
			}

			return true;
		}
	}
}
