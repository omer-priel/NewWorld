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
using System.Reflection;

namespace NewWorldVisualStudioPlugin.Commands
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class OpenWithVSCode
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
        /// VS Package that provides this command, not null.
        /// </summary>
        private readonly AsyncPackage package;

        /// <summary>
        /// Initializes a new instance of the <see cref="OpenWithVSCode"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        /// <param name="commandService">Command service to add command to, not null.</param>
        private OpenWithVSCode(AsyncPackage package, OleMenuCommandService commandService)
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

        // Members
        private string Name = "Open With VS Code";

        // TODO: 
        private T GetService<T>()
        {
            var task = ServiceProvider.GetServiceAsync(typeof(T));
            task.Wait();

            return (T)task.Result;
        }

        // way 1
        public void IdentifyInternalObjectTypes(UIHierarchyItem item)
        {
            if (item.Object is Solution)
            {
                Solution solution = item.Object as Solution;

                Utilities.ErrorMessage(package, "<<Solution>>");

            }
            else if (item.Object is Project)
            {
                Utilities.ErrorMessage(package, "<<Project>>");
            }
            else if (item.Object is EnvDTE80.SolutionFolder)
            {
                Utilities.ErrorMessage(package, "<<SolutionFolder>>");
            }
            else
            {
                Assembly[] loadedAssemblies = AppDomain.CurrentDomain.GetAssemblies();

                for (Int32 index = 0; index < loadedAssemblies.Length; index++)
                {
                    try
                    {
                        IdentifyInternalObjectTypes(item, loadedAssemblies[index]);
                    }
                    catch
                    {

                    }
                }

                Utilities.ErrorMessage(package, "END");
            }
        }

        public void IdentifyInternalObjectTypes(UIHierarchyItem item, Assembly assemblyToCheck)
        {
            Type[] exportedTypes = assemblyToCheck.GetExportedTypes();

            for (Int32 index = 0; index < exportedTypes.Length; index++)
            {
                if (exportedTypes[index].IsInstanceOfType(item.Object))
                {
                    Utilities.ErrorMessage(package, exportedTypes[index].FullName);
                }
            }
        }

        // Execute
        private void Execute(object sender, EventArgs e)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            // TODO: Get Solution / Project / Folder path
            string folderPath = System.Windows.Forms.Application.StartupPath;

            DTE2 dte = (DTE2)GetService<SDTE>();

            var arr = GetItemFolder.Load(dte);
            foreach (var item in arr)
            {
                Utilities.ErrorMessage(package, Enum.GetName(typeof(Test.SelectionTypes), item));
            }


            return;
            Array selectedItems = (Array)dte.ToolWindows.SolutionExplorer.SelectedItems;

            if (null != selectedItems)
            {
                foreach (UIHierarchyItem selectedItem in selectedItems)
                {
                    IdentifyInternalObjectTypes(selectedItem);
                }
            }

            return;

            folderPath = new System.IO.FileInfo(dte.Solution.FullName).Directory.FullName;
            Utilities.ErrorMessage(package, folderPath);

            try
            {
                string codePath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
                codePath = codePath.Remove(codePath.Length - 8, 8);
                codePath += "\\Local\\Programs\\Microsoft VS Code\\Code.exe";

                if (!System.IO.File.Exists(codePath))
                {
                    Utilities.ErrorMessage(this.package, "Visual Studio Code does not installed!");
                    return;
                }

                System.Diagnostics.Process.Start(codePath, folderPath);
            }
            catch
            {
                Utilities.ErrorMessage(this.package, "Can't open Visual Studio Code!");
            }
        }
    }
}
