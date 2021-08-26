// extension - The global Extension class

import * as vscode from 'vscode';

// Classes
// Solution settings
export class Solution {
    name: string;
    path: String;
    uri: vscode.Uri;

    constructor() {
        this.name = '';
        this.path = '';
        this.uri = vscode.Uri.parse("");
    }

    isNewWorldEngine() {
        return this.name === 'NewWorld';
    }
}

// Extension settings
export class Extension {
    title: String;
    name: String;
    contextData: vscode.ExtensionContext | null;

    constructor() {
		this.title = '';
        this.name = '';
		this.contextData = null;
    }

	setContext(context: vscode.ExtensionContext) {
		this.title = 'New World';
        this.name = 'newworld';
		this.contextData = context;
	}

	clearContext() {
		this.title = '';
        this.name = '';
		this.contextData = null;
	}

	context(): vscode.ExtensionContext {
		return this.contextData as vscode.ExtensionContext;
	}
}

// Members
export let solution: Solution;
export let extension: Extension;

// Functions
// Load Solution
export function loadSolution(context: vscode.ExtensionContext) {
	solution = new Solution();

	if (vscode.workspace.workspaceFolders !== undefined && vscode.workspace.workspaceFolders.length === 1) {
		solution.name = vscode.workspace.workspaceFolders[0].name;
		solution.path = vscode.workspace.workspaceFolders[0].uri.fsPath;
		solution.uri = vscode.workspace.workspaceFolders[0].uri;
	}

	extension = new Extension();
	extension.setContext(context);
}

// Unload Solution
export function unloadSolution() {
	solution = new Solution();

	extension = new Extension();
	extension.clearContext();
}