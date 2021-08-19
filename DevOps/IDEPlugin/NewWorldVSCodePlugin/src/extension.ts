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

	inputBox.onDidAccept(async () => {

		inputBox.hide();
		
		let inputClassName: String = inputBox.value;

		if (inputClassName.length === 0) {
			vscode.window.showErrorMessage('Class must have a name!');
			return;
		}

		let newWord = true;
		let className = '';
		for (let i = 0; i < inputClassName.length; i++) {
			
			let inputChar = inputClassName[i];
			if (inputChar === ' ') {

				newWord = true;
			} else if (inputChar === '_') {
				
				newWord = true;
				className += inputChar;
			} else {
		
				let flag = 'a' <= inputChar && inputChar <= 'z';
				flag = flag || 'A' <= inputChar && inputChar <= 'Z';
				flag = flag || '0' <= inputChar && inputChar <= '9';

				if (!flag) {

					vscode.window.showErrorMessage('Class names can contain letters, digits and underscores!');
					return;
				}

				if (newWord) {
					
					className += inputChar.toUpperCase();
					newWord = false;
				} else {

					className += inputChar;
				}
			}
		}

		
		if (className[0] < 'A' || 'Z' < className[0]) {
			
			vscode.window.showErrorMessage('Class names must begin with upper letter!');
			return;
		}

		log(folderUri.fsPath);
		
		let headerUri = vscode.Uri.joinPath(folderUri, './' + className + '.h');
		let sourceUri = vscode.Uri.joinPath(folderUri, './' + className + '.cpp');

		log(headerUri.fsPath);
		log(sourceUri.fsPath);
		
		let headerContent = `#pragma once

class ClasName
{
	public:

};`;

		let sourceContent = '#include "ClasName.h"\n';

		log(headerContent);
		headerContent.replace('ClasName', className);
		log(headerContent);

		headerContent = headerContent.replace('ClasName', className);
		sourceContent = sourceContent.replace('ClasName', className);

		await vscode.workspace.fs.writeFile(headerUri, Buffer.from(headerContent, 'utf8'));
		await vscode.workspace.fs.writeFile(sourceUri, Buffer.from(sourceContent, 'utf8'));

		vscode.window.showTextDocument(headerUri);
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