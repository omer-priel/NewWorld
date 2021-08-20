using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Management;
using Microsoft.Win32;

namespace NewWorldWindowsPlugin
{
	public class WindowsAPI
	{
		private class Import
		{
			// Windows API
			public const int SW_SHOW = 5;
			public const int SW_HIDE = 0;

			[DllImport("kernel32.dll")]
			static public extern IntPtr GetConsoleWindow();

			[DllImport("user32.dll")]
			static public extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

			[DllImport("Shell32.dll", CharSet = CharSet.Auto, SetLastError = true)]
			static public extern void SHChangeNotify(uint wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2);
		}

		// Actions
		static public void ShowConsole(bool show)
		{
			IntPtr handle = Import.GetConsoleWindow();

			Import.ShowWindow(handle, show ? Import.SW_SHOW : Import.SW_HIDE);
		}

		static private bool isConsole = false;
		static private bool isConsoleCache = false;

		static public bool IsConsole()
		{
			if (!isConsoleCache)
			{
				try
				{
					var query = new ManagementObjectSearcher("SELECT * FROM Win32_Process WHERE ProcessId = " + Process.GetCurrentProcess().Id);

					Process parent = query.Get().OfType<ManagementObject>().Select(p => Process.GetProcessById((int)(uint)p["ParentProcessId"])).FirstOrDefault();
					isConsole = parent.ProcessName == "cmd";
				}
				catch
				{
					isConsole = false;
				}
				isConsoleCache = true;
			}

			return isConsole;
		}

		static public void UpdateRegistry()
		{
			Import.SHChangeNotify(0x08000000, 0x0000, IntPtr.Zero, IntPtr.Zero);
		}

		static public void DeleteRegistrykey(RegistryKey root, string parentkey, string keyName)
		{
			RegistryKey reg;
			if (parentkey == null)
			{
				reg = root.OpenSubKey(keyName, false);
			}
			else
			{
				reg = root.OpenSubKey(parentkey + "\\" + keyName, false);
			}

			if (reg != null)
			{
				reg.Close();

				if (parentkey == null)
				{
					root.DeleteSubKeyTree(keyName);
				}
				else
				{
					RegistryKey parentReg = root.OpenSubKey(parentkey, true);
					parentReg.DeleteSubKeyTree(keyName);
					parentReg.Close();
				}
			}
		}
	}
}
