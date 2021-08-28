using System;
using System.ComponentModel.Design;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.Shell;

namespace NewWorldVisualStudioExtension
{
	public abstract class Command
	{
		public string Name;
		public bool OnlyOnNewWorldEngine;
		protected readonly AsyncPackage package;

		public Command(string name, bool onlyOnNewWorldEngine, AsyncPackage package, OleMenuCommandService commandService, int CommandId, Guid CommandSet)
		{
			this.Name = name;
			this.OnlyOnNewWorldEngine = onlyOnNewWorldEngine;
			this.package = package ?? throw new ArgumentNullException(nameof(package));

			commandService = commandService ?? throw new ArgumentNullException(nameof(commandService));

			var menuCommandID = new CommandID(CommandSet, CommandId);

			if (!onlyOnNewWorldEngine || Utilities.IsNewWorldSolution(package))
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

		// abstract functions
		abstract public void Execute(object sender, EventArgs e);

		// Getters
		protected T GetService<T>()
        {
            var task = package.GetServiceAsync(typeof(T));
            task.Wait();

            return (T)task.Result;
        }
	}
}
