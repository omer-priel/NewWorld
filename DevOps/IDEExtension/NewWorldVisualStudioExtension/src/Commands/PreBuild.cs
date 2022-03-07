﻿using Microsoft.VisualStudio.Shell;
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
using Microsoft.VisualStudio.VCProjectEngine;

namespace NewWorldVisualStudioExtension.Commands
{
    internal sealed class PreBuild : Command
    {
        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0103;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("e2f2287e-ebb0-4eb0-850f-5c7de314a263");

        /// <summary>
        /// Initializes a new instance of the <see cref="NewClass"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        /// <param name="commandService">Command service to add command to, not null.</param>
        private PreBuild(AsyncPackage package, OleMenuCommandService commandService)
            : base("New World Pre Build", true, package, commandService, CommandId, CommandSet)
        {
            
        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static PreBuild Instance
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
            Instance = new PreBuild(package, commandService);
        }

        // Execute
        public override void Execute(object sender, EventArgs e)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            DTE2 dte = (DTE2)GetService<SDTE>();
            EnvDTE100.Solution4 solution = (EnvDTE100.Solution4)dte.Solution;

            // Get Folder Path
            string folderPath = new System.IO.FileInfo(solution.FullName).Directory.Parent.FullName;

            // Get File Name
            Utilities.ErrorMessage(this.package, folderPath);

            //Utilities.ErrorMessage(this.package, (solution.SolutionBuild.StartupProjects));
            //solution.SolutionBuild.StartupProjects;

            /*
            foreach (Project project in solution.Projects)
            {
                Microsoft.VisualStudio.VCProjectEngine.VCProject vcProject
                    = project.Object as Microsoft.VisualStudio.VCProjectEngine.VCProject;

                //Utilities.ErrorMessage(this.package, vcProject.Name);
            }
            */
        }
    }
}
