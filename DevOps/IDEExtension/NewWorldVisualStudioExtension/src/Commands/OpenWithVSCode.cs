using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using System;
using System.ComponentModel.Design;
using System.Globalization;
using System.Threading;
using System.Threading.Tasks;
using Task = System.Threading.Tasks.Task;

using EnvDTE;
using EnvDTE80;

namespace NewWorldVisualStudioExtension.Commands
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class OpenWithVSCode : Command
    {
        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0102;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("e2f2287e-ebb0-4eb0-850f-5c7de314a263");

        /// <summary>
        /// Initializes a new instance of the <see cref="OpenWithVSCode"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        /// <param name="commandService">Command service to add command to, not null.</param>
        private OpenWithVSCode(AsyncPackage package, OleMenuCommandService commandService)
            : base("Open With VSCode", true, package, commandService, CommandId, CommandSet)
        {

        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static OpenWithVSCode Instance
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the service provider from the owner package.
        /// </summary>
        private Microsoft.VisualStudio.Shell.IAsyncServiceProvider ServiceProvider
        {
            get
            {
                return this.package;
            }
        }

        /// <summary>
        /// Initializes the singleton instance of the command.
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        public static async Task InitializeAsync(AsyncPackage package)
        {
            // Switch to the main thread - the call to AddCommand in OpenWithVSCode's constructor requires
            // the UI thread.
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync(package.DisposalToken);

            OleMenuCommandService commandService = await package.GetServiceAsync(typeof(IMenuCommandService)) as OleMenuCommandService;
            Instance = new OpenWithVSCode(package, commandService);
        }

        // Execute
        public override void Execute(object sender, EventArgs e)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            string filePath = Utilities.GetNewWorldFilePath(package);

            if (filePath != null)
			{
                System.Diagnostics.Process.Start("NewWorldPlugin", filePath);
            }
        }
    }
}
