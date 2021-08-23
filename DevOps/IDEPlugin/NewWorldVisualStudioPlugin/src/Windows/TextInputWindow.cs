using Microsoft.VisualStudio.Shell;
using System;
using System.Runtime.InteropServices;

namespace NewWorldVisualStudioPlugin.Windows
{
    /// <summary>
    /// This class implements the tool window exposed by this package and hosts a user control.
    /// </summary>
    /// <remarks>
    /// In Visual Studio tool windows are composed of a frame (implemented by the shell) and a pane,
    /// usually implemented by the package implementer.
    /// <para>
    /// This class derives from the ToolWindowPane class provided from the MPF in order to use its
    /// implementation of the IVsUIElementPane interface.
    /// </para>
    /// </remarks>
    [Guid("e82ea2a3-affb-4950-8b32-9aa3eaaa32a9")]
    public class TextInputWindow : ToolWindowPane
    {
        public static string GUID_ID = "e82ea2a3-affb-4950-8b32-9aa3eaaa32a9";

        /// <summary>
        /// Initializes a new instance of the <see cref="TextInputWindow"/> class.
        /// </summary>
        public TextInputWindow() : base(null)
        {
            this.Caption = "TextInputWindow";

            // This is the user control hosted by the tool window; Note that, even if this class implements IDisposable,
            // we are not calling Dispose on this object. This is because ToolWindowPane calls Dispose on
            // the object returned by the Content property.
            this.Content = new TextInputWindowControl();
        }
    }
}
