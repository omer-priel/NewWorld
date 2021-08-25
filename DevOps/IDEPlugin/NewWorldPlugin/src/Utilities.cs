﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace NewWorldPlugin
{
	static public class Utilities
	{
		// Show Error Message
		static public void ErrorMessage(string message)
		{
			if (!WindowsAPI.IsConsole())
			{
				MessageBox.Show("Error: " + message, Plugin.Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			else
			{
				Console.WriteLine("Error: {0}\n", message);
				Commands.Help();
			}
		}

		// Call DevOps's Script
		static public void StartDevOpsScript(string name)
		{
			try
			{
				WindowsAPI.ShowConsole(true);

				string applicationFolder = Application.StartupPath;
				DirectoryInfo directory = new DirectoryInfo(applicationFolder);

				string devOpsPath = directory.Parent.Parent.Parent.Parent.FullName;
				string pythonPath = devOpsPath + @"\Scripts\venv\Scripts\python.exe";
				string scriptPath = devOpsPath + @"\Scripts\src\" + name + ".py";

				Process process = new Process();
				ProcessStartInfo startInfo = new ProcessStartInfo(pythonPath);
				startInfo.Arguments = scriptPath;
				startInfo.WorkingDirectory = devOpsPath;
				startInfo.RedirectStandardOutput = true;
				startInfo.UseShellExecute = false;

				process.StartInfo = startInfo;

				process.OutputDataReceived += (sender, argsx) => Console.WriteLine(argsx.Data);
				process.Start();

				process.BeginOutputReadLine();
				process.WaitForExit();
			}
			catch (Exception ex)
			{
				ErrorMessage(ex.Message);
			}
		}
	}
}
