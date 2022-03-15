using System;
using System.ComponentModel.Design;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

using EnvDTE;
using EnvDTE80;

namespace NewWorldVisualStudioExtension
{
	public abstract class Command
	{
		public string Name;
		public bool OnlyOnNewWorldEngine;
		protected readonly AsyncPackage package;

		private MenuCommand MenuCommand;

		public Command(string name, bool onlyOnNewWorldEngine, AsyncPackage package, OleMenuCommandService commandService, int CommandId, Guid CommandSet)
		{
			this.Name = name;
			this.OnlyOnNewWorldEngine = onlyOnNewWorldEngine;
			this.package = package ?? throw new ArgumentNullException(nameof(package));

			commandService = commandService ?? throw new ArgumentNullException(nameof(commandService));

			var menuCommandID = new CommandID(CommandSet, CommandId);

			MenuCommand = new MenuCommand(this.FullExecte, menuCommandID);

			SolutionEvents_Opened();

			DTE2 dte = GetDTE();
			dte.Events.SolutionEvents.Opened += SolutionEvents_Opened;

			commandService.AddCommand(MenuCommand);
		}

		private void SolutionEvents_Opened()
		{
			MenuCommand.Visible = !this.OnlyOnNewWorldEngine || Utilities.IsNewWorldSolution(package);
		}

		// Actions
		public void FullExecte(object sender, EventArgs e)
		{
			if (MenuCommand.Visible)
			{
				Execute(sender, e);
			}
		}

		// abstract functions
		abstract public void Execute(object sender, EventArgs e);

		// Getters
		protected T GetService<T>()
        {
            var task = package.GetServiceAsync(typeof(T));
            task.Wait();

            return (T)task.Result;
        }

		public DTE2 GetDTE()
		{
			DTE2 dte = (DTE2)GetService<SDTE>();
			return dte;
		}
	}
}
