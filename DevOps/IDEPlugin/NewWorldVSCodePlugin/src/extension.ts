import * as vscode from 'vscode';

class Solution {
    name: string;
    path: String;
    uri: vscode.Uri;
   
    constructor() {
        this.name = '';
        this.path = '';
        this.uri = vscode.Uri.parse("");
    }

    isNewWorldEngine() {
        return this.name !== '';
    }
}

class Plugin {
    title: String;
    name: String;
    context: vscode.ExtensionContext;

    constructor(context: vscode.ExtensionContext) {
        this.title = 'New World';
        this.name = 'newworld';
        this.context = context;
    }
}

// global
declare global {
    var solution: Solution;
    var plugin: Plugin;
}

// load Solution
function loadSolution() {
    global.solution = new Solution();

    if (vscode.workspace.workspaceFolders !== undefined && vscode.workspace.workspaceFolders.length === 1) {
        
        global.solution.name = vscode.workspace.workspaceFolders[0].name;
        global.solution.path = vscode.workspace.workspaceFolders[0].uri.fsPath;
        global.solution.uri = vscode.workspace.workspaceFolders[0].uri;
    }
}

// log funtions
function log(message?: any, ...optionalParams: any[]) {
    console.log(global.plugin.title + ": " + message);
}

function dir(obj: any) {
    log("dir");
    console.dir(obj);
}

// plugin commands
function pushVSCodeCommand(name: String, callback: (...args: any[]) => any, thisArg?: any) {
    if (!global.solution.isNewWorldEngine()) {
        callback = (...args: any[]) => {
            vscode.window.showInformationMessage('Is not New World project!');
        };    
    }

    let command = vscode.commands.registerCommand(global.plugin.name + "." + name, callback);
    global.plugin.context.subscriptions.push(command);
}

export function activate(context: vscode.ExtensionContext) {

    global.plugin = new Plugin(context);

    loadSolution();

	pushVSCodeCommand('action1' , () => {

		vscode.window.showInformationMessage('New World action1! ');
	});

    pushVSCodeCommand('action2' , () => {

		vscode.window.showInformationMessage('New World action2! ');
	});

    pushVSCodeCommand('action3' , () => {
        
        dir(global.solution);
        log(global.solution.name);
        dir(global.plugin);
	});
}

export function deactivate() {

    global.solution = new Solution();
}