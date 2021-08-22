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

        static public void ErrorMessage(AsyncPackage package, object message)
        {
            VsShellUtilities.ShowMessageBox(package, message.ToString(), PluginName
                , OLEMSGICON.OLEMSGICON_CRITICAL, OLEMSGBUTTON.OLEMSGBUTTON_OK, OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST);
        }
    }
}
