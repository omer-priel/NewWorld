import * as vscode from 'vscode';
import * as fs from 'fs';

import global = require('./global');
import utilities = require('./utilities');
import commands = require('./commands');

// Extension actions
function pushVSCodeCommand(name: String, callback: (...args: any[]) => any) {
    
	let commandId = global.extension.name + "." + name;
	
	if (!global.solution.isNewWorldEngine()) {
        callback = (...args: any[]) => {
            vscode.window.showInformationMessage('Is not New World project!');
        };
    }

    let command = vscode.commands.registerCommand(commandId, callback);
    global.extension.context().subscriptions.push(command);
}

// activate the Extension
export function activate(context: vscode.ExtensionContext) {

    global.loadSolution(context);

	vscode.commands.executeCommand('setContext', 'isNewWorldEngine', global.solution.isNewWorldEngine());

	pushVSCodeCommand('newClass', commands.newClass);
	pushVSCodeCommand('generateProjects', commands.generateProjects);
	pushVSCodeCommand('build', commands.build);
}

// deactivate the Extension
export function deactivate() {

    global.unloadSolution();
}