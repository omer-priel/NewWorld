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
		static public string NewWorldFilePath = null;
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

		// load .nwe file
		static public bool LoadNWEFile(string filePath)
		{
			NewWorldFilePath = filePath;

			NewWorldFile = new FileInfo(NewWorldFilePath);

			if (!NewWorldFile.Exists)
			{
				Utilities.ShowErrorMessage("The path \"" + filePath + "\" does not exists!");
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
