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

namespace NewWorldVisualStudioPlugin.Commands
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class NewFile
    {
        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0100;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("e2f2287e-ebb0-4eb0-850f-5c7de314a263");

        /// <summary>
        /// VS Package that provides this command, not null.
        /// </summary>
        private readonly AsyncPackage package;

        /// <summary>
        /// Initializes a new instance of the <see cref="NewFile"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        /// <param name="commandService">Command service to add command to, not null.</param>
        private NewFile(AsyncPackage package, OleMenuCommandService commandService)
        {
            this.package = package ?? throw new ArgumentNullException(nameof(package));
            commandService = commandService ?? throw new ArgumentNullException(nameof(commandService));

            var menuCommandID = new CommandID(CommandSet, CommandId);
            var menuItem = new MenuCommand(this.Execute, menuCommandID);
            commandService.AddCommand(menuItem);
        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static NewFile Instance
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
            // Switch to the main thread - the call to AddCommand in NewFile's constructor requires
            // the UI thread.
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync(package.DisposalToken);

            OleMenuCommandService commandService = await package.GetServiceAsync(typeof(IMenuCommandService)) as OleMenuCommandService;
            Instance = new NewFile(package, commandService);
        }

        // Members
        private string Name = "New File";

        // Getters
        protected T GetService<T>()
        {
            var task = ServiceProvider.GetServiceAsync(typeof(T));
            task.Wait();

            return (T)task.Result;
        }

        // Execute
        private void Execute(object sender, EventArgs e)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            DTE2 dte = (DTE2)GetService<SDTE>();

            string folderPath = new System.IO.FileInfo(dte.Solution.FullName).Directory.Parent.FullName;

            Array selectedItems = (Array)dte.ToolWindows.SolutionExplorer.SelectedItems;
            if (null != selectedItems && selectedItems.Length > 0)
            {
                foreach (UIHierarchyItem selectedItem in selectedItems)
                {
                    folderPath += "\\" + GetItemFolder.GetPath(selectedItem);
                    break;
                }
            }
            else
            {
                Utilities.ErrorMessage(this.package, "Can't find the selected folder!");
                return;
            }

            // Get Folder Path
            string folderPath = new System.IO.FileInfo(dte.Solution.FullName).Directory.Parent.FullName;

            Array selectedItems = (Array)dte.ToolWindows.SolutionExplorer.SelectedItems;
            if (null != selectedItems && selectedItems.Length > 0)
            {
                foreach (UIHierarchyItem selectedItem in selectedItems)
                {
                    folderPath += "\\" + GetItemFolder.GetPath(selectedItem);
                    break;
                }
            }
            else
            {
                Utilities.ErrorMessage(this.package, "Can't find the selected folder!");
                return;
            }

            // Get File Name
            Utilities.ErrorMessage(package, folderPath);

            var window = dte.Windows.Item("{ID}");
            window.Visible = true;
        }
    }
}
