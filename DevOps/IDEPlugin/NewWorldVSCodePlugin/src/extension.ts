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

// utilites
function pushVSCodeCommand(name: String, callback: (...args: any[]) => any) {
    
	let commandId = global.plugin.name + "." + name;
	
	if (!global.solution.isNewWorldEngine()) {
        callback = (...args: any[]) => {
            vscode.window.showInformationMessage('Is not New World project!');
        };
    }

    let command = vscode.commands.registerCommand(commandId, callback);
    global.plugin.context.subscriptions.push(command);
}

// commands
function newClass(folderUriPath: string) {

	if (folderUriPath === undefined) {
		vscode.window.showErrorMessage('Undefined folder path!');	
		return;
	}
	let folderUri = vscode.Uri.parse(folderUriPath);

	let inputBox = vscode.window.createInputBox();
	inputBox.title = "Class Name";
	log(inputBox.title);

	inputBox.onDidAccept(() => {

		inputBox.hide();
		
		let className: String = inputBox.value;

		if (className.length === 0) {
			vscode.window.showErrorMessage('Class must have a name!');
			return;
		}

		className = className.replace(' ', '');

		if ('a' <= className[0] && className[0] <= 'z' || 'A' <= className[0] && className[0] <= 'Z') {
			
			className =  className[0].toUpperCase() + className.substring(1);
		} else {
			
			vscode.window.showErrorMessage('Class names must begin with upper letter!');
			return;
		}

		for (let i = 1; i < className.length; i++) {
			
			let flag = 'a' <= className[i] && className[i] <= 'z';
			flag = flag || 'A' <= className[i] && className[i] <= 'Z';
			flag = flag || '0' <= className[i] && className[i] <= '9';
			flag = flag || className[i] === '_';

			if (!flag) {
			
				vscode.window.showErrorMessage('Class names can contain letters, digits and underscores!');
				return;
			}
		}

		log(folderUri.fsPath);
		let headerUri = vscode.Uri.joinPath(folderUri, './' + className + '.h');
		log(headerUri.fsPath);
	
		//vscode.workspace.fs.writeFile(folderUri)
	});
	
	inputBox.show();
}

function generateProjects()  {

	vscode.window.showInformationMessage('New World generateProjects!');
}

function build() {

	vscode.window.showInformationMessage('New World build!');
}

// activate / deactivate
export function activate(context: vscode.ExtensionContext) {

    global.plugin = new Plugin(context);

    loadSolution();

	vscode.commands.executeCommand('setContext', 'isNewWorldEngine', global.solution.isNewWorldEngine());

	pushVSCodeCommand('newClass', newClass);
	pushVSCodeCommand('generateProjects', generateProjects);
	pushVSCodeCommand('build', build);
}

export function deactivate() {

    global.solution = new Solution();
}