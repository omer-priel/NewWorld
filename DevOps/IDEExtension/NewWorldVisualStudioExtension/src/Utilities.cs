using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using System.IO;
using EnvDTE80;

namespace NewWorldVisualStudioExtension
{
    class Utilities
    {
        // Extension Settings
        static string ExtensionName = "New World";

        // Print Error Message
        static public void ErrorMessage(AsyncPackage package, object message)
        {
            VsShellUtilities.ShowMessageBox(package, message.ToString(), ExtensionName
                , OLEMSGICON.OLEMSGICON_CRITICAL, OLEMSGBUTTON.OLEMSGBUTTON_OK, OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST);
        }

        // Get Service from the Extension Package
        static public T GetService<T>(AsyncPackage package)
        {
            var task = package.GetServiceAsync(typeof(T));
            task.Wait();

            return (T)task.Result;
        }

        // Check if is New World Solution
        static public bool IsNewWorldSolution(AsyncPackage package)
        {
            try
            {
                DTE2 dte = (DTE2)GetService<SDTE>(package);
                if (dte.Solution != null)
                {
                    return new FileInfo(dte.Solution.FullName).Name == "NewWorld.sln";
                }
            }
            catch { }

            return false;
        }

        // Get Path of the file NewWorld.nwe
        static public string GetNewWorldFilePath(AsyncPackage package)
		{
            ThreadHelper.ThrowIfNotOnUIThread();

            DTE2 dte = (DTE2)GetService<SDTE>(package);

            DirectoryInfo directory = new FileInfo(dte.Solution.FullName).Directory;

            do
            {
                string filePath = directory.FullName + "\\NewWorld.nwe";
                if (File.Exists(filePath))
				{
                    return filePath;
				}

                directory = directory.Parent;
            }
            while (directory != directory.Root);

            return null;
        }
    }
}
