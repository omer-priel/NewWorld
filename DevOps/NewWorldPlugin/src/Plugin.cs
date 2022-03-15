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
		static public bool LoadProject(string rootPath)
		{
			DirectoryInfo rootDirectory = new DirectoryInfo(rootPath);
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
					Utilities.ShowErrorMessage("The .nwe does not exists!");
					return false;
				}

				rootDirectory = rootDirectory.Parent;

			}

			return true;
		}
	}
}
