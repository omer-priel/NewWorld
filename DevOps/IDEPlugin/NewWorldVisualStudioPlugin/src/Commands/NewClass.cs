using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using System;
using System.ComponentModel.Design;
using System.Globalization;
using System.Threading;
using System.Threading.Tasks;
using Task = System.Threading.Tasks.Task;

using System.Collections.Generic;

using EnvDTE;
using EnvDTE80;

namespace NewWorldVisualStudioPlugin.Commands
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class NewClass
    {
        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0101;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("e2f2287e-ebb0-4eb0-850f-5c7de314a263");

        /// <summary>
        /// VS Package that provides this command, not null.
        /// </summary>
        private readonly AsyncPackage package;

        /// <summary>
        /// Initializes a new instance of the <see cref="NewClass"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        /// <param name="commandService">Command service to add command to, not null.</param>
        private NewClass(AsyncPackage package, OleMenuCommandService commandService)
        {
            this.package = package ?? throw new ArgumentNullException(nameof(package));
            commandService = commandService ?? throw new ArgumentNullException(nameof(commandService));

            var menuCommandID = new CommandID(CommandSet, CommandId);

            if (Utilities.IsNewWorldSolution(package))
            {
                var menuItem = new MenuCommand(this.Execute, menuCommandID);
                menuItem.Visible = true;
                commandService.AddCommand(menuItem);
            }
            else
            {
                var menuItem = new MenuCommand(Utilities.EmptyExecute, menuCommandID);
                menuItem.Visible = false;
                commandService.AddCommand(menuItem);
            }
        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static NewClass Instance
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
            // Switch to the main thread - the call to AddCommand in NewClass's constructor requires
            // the UI thread.
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync(package.DisposalToken);

            OleMenuCommandService commandService = await package.GetServiceAsync(typeof(IMenuCommandService)) as OleMenuCommandService;
            Instance = new NewClass(package, commandService);
        }


        // Members
        private string Name = "New Class";

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
            string className = Windows.TextInputWindow.GetValue("Class Name");

            if (className != null)
            {
                // Create New Class
                CreateNewClass(dte, folderPath, className);
            }
        }

        private void CreateNewClass(DTE2 dte, string folderPath, string classNameInput)
        {
            bool newWord = true;
            string className = "";
            for (int i = 0; i < classNameInput.Length; i++)
            {
                char inputChar = classNameInput[i];
                if (inputChar == ' ')
                {
                    newWord = true;
                }
                else if (inputChar == '_')
                {
                    newWord = true;
                    className += inputChar;
                }
                else
                {
                    bool flag = 'a' <= inputChar && inputChar <= 'z';
                    flag = flag || 'A' <= inputChar && inputChar <= 'Z';
                    flag = flag || '0' <= inputChar && inputChar <= '9';

                    if (!flag)
                    {

                        Utilities.ErrorMessage(this.package, "Class names can contain letters, digits and underscores!");
                        return;
                    }

                    if (newWord)
                    {
                        if ('a' <= inputChar && inputChar <= 'z')
                        {
                            inputChar -= 'a';
                            inputChar += 'A';
                        }

                        className += inputChar;
                        newWord = false;
                    }
                    else
                    {
                        className += inputChar;
                    }
                }
            }

            if (className.Length == 0)
            {
                Utilities.ErrorMessage(this.package, "The class must have a name!");
                return;
            }

            if (className[0] < 'A' || 'Z' < className[0])
            {

                Utilities.ErrorMessage(this.package, "Class names must begin with upper letter!");
                return;
            }

            string headerPath = folderPath + "\\" + className + ".h";
            string sourcePath = folderPath + "\\" + className + ".cpp";


            if (System.IO.File.Exists(headerPath))
            {

                if (System.IO.File.Exists(sourcePath))
                {

                    Utilities.ErrorMessage(this.package, "The class " + className + " already exists!");
                }
                else
                {

                    Utilities.ErrorMessage(this.package, "The header " + className + ".h already exists!");
                }
                return;
            }

            if (System.IO.File.Exists(sourcePath))
            {

                Utilities.ErrorMessage(this.package, "The source " + className + ".cpp already exists!");
                return;
            }

            dte.StatusBar.Text = "Create new Class: " + className;

            try
            {
                var haederFile = System.IO.File.CreateText(headerPath);
                haederFile.WriteLine("#pragma once");
                haederFile.WriteLine("");
                haederFile.WriteLine("class " + className);
                haederFile.WriteLine("{");
                haederFile.WriteLine("\tpublic:");
                haederFile.WriteLine("\t");
                haederFile.WriteLine("}");
                haederFile.Close();

                var sourceFile = System.IO.File.CreateText(sourcePath);
                sourceFile.WriteLine("#include \"" + className + ".h\"");
                sourceFile.Close();
            }
            catch (Exception ex)
            {
                Utilities.ErrorMessage(this.package, "Can't create the class " + className + "!");
                return;
            }

            dte.StatusBar.ShowTextUpdates(false);

            dte.StatusBar.Text = "The class " + className + " Created ";

            dte.ItemOperations.OpenFile(sourcePath);
            dte.ItemOperations.OpenFile(headerPath);
        }
    }
}
