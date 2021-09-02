﻿using Microsoft.VisualStudio.Shell;
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
    internal sealed class NewFile : Command
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
        /// Initializes a new instance of the <see cref="NewFile"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        /// <param name="commandService">Command service to add command to, not null.</param>
        private NewFile(AsyncPackage package, OleMenuCommandService commandService)
            : base("New File", false, package, commandService, CommandId, CommandSet)
        {

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
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync(package.DisposalToken);

            OleMenuCommandService commandService = await package.GetServiceAsync(typeof(IMenuCommandService)) as OleMenuCommandService;
            Instance = new NewFile(package, commandService);
        }

        // Execute
        public override void Execute(object sender, EventArgs e)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            DTE2 dte = (DTE2)GetService<SDTE>();

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
            string fileName = Windows.TextInputWindow.GetValue("File Name");

            if (fileName != null && fileName != "")
            {
                fileName = fileName.Replace('/', '\\');

                // Create New File

                string filePath = folderPath + "\\" + fileName;
                if (!System.IO.File.Exists(filePath))
                {
                    dte.StatusBar.Text = "Create new file: " + filePath;

                    try
                    {
                        if (fileName.IndexOf('\\') != -1) // subfolder
						{
                            string subFolder = fileName.Substring(0, fileName.LastIndexOf('\\'));
                            System.IO.Directory.CreateDirectory(folderPath + "\\" + subFolder);
                        }

                        var file = System.IO.File.CreateText(filePath);
                        file.Close();

                    }
                    catch
                    {
                        Utilities.ErrorMessage(this.package, "Can't create the file \"" + filePath + "\"!");
                        return;
                    }

                    dte.StatusBar.ShowTextUpdates(false);

                    dte.StatusBar.Text = "The file \"" + filePath + "\" Created ";

                    // Open the file in the IDE
                    dte.ItemOperations.OpenFile(filePath);
                }
                else
                {
                    Utilities.ErrorMessage(this.package, "The file \"" + fileName + "\" aleady exists!");
                    return;
                }
            }
        }
    }
}