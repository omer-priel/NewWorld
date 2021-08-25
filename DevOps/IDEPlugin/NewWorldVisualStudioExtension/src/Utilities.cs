﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
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
            return true; // Add this Extension not only for NewWorld.

            try
            {
                DTE2 dte = (DTE2)GetService<SDTE>(package);
                if (dte.Solution != null)
                {
                    return new System.IO.FileInfo(dte.Solution.FullName).Name == "NewWorld.sln";
                }
            }
            catch { }

            return false;
        }

        // If is not New World Solution this command run
        static public void EmptyExecute(object sender, EventArgs e)
        {

        }
    }
}
