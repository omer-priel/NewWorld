using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace NewWorldPlugin
{
	static public class Utilities
	{
		// Show Error Message
		static public void ShowErrorMessage(string message)
		{
			if (!WindowsAPI.IsConsole())
			{
				MessageBox.Show("Error: " + message, Plugin.Title, MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			else
			{
				Console.WriteLine("Error: {0}", message);
				Commands.Help();
			}
		}

		// Call DevOps's Script
		static public void CallDevOpsScript(string name)
		{
			try
			{
				WindowsAPI.ShowConsole(true);

				string devOpsPath = Plugin.GetPath(@"DevOps");
				string pythonPath = Plugin.GetPath(@"DevOps\Scripts\env\Scripts\python.exe");
				string scriptPath = Plugin.GetPath(@"DevOps\Scripts\src\" + name + ".py");

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
				ShowErrorMessage(ex.Message);
			}
		}
	}
}
