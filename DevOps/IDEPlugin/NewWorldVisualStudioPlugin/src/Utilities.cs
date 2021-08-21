using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

namespace NewWorldVisualStudioPlugin
{
    class Utilities
    {
        static string PluginName = "New World";

        static public void ErrorMessage(AsyncPackage package, string message)
        {
            VsShellUtilities.ShowMessageBox(package, message, PluginName
                , OLEMSGICON.OLEMSGICON_CRITICAL, OLEMSGBUTTON.OLEMSGBUTTON_OK, OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST);
        }
    }
}
