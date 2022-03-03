// commands - All the extension Commands

import * as vscode from 'vscode';
import * as fs from 'fs';

import global = require('./global');
import utilities = require('./utilities');

// The "New Class" Command
export function newClass(folderUriPath: string) {

	if (folderUriPath === undefined) {
	
		vscode.window.showErrorMessage('Undefined folder path!');	
		return;
	}
	
	let folderUri = vscode.Uri.parse(folderUriPath);

	let inputBox = vscode.window.createInputBox();
	inputBox.title = "Class Name";

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

		let headerUri = vscode.Uri.joinPath(folderUri, './' + className + '.h');
		let sourceUri = vscode.Uri.joinPath(folderUri, './' + className + '.cpp');

		if (fs.existsSync(headerUri.fsPath)) {

			if (fs.existsSync(sourceUri.fsPath)) {

				vscode.window.showErrorMessage('The class ' + className + ' already exists!');	
			} else {

				vscode.window.showErrorMessage('The header ' + className + '.h already exists!');	
			}
		
			return;
		}

		if (fs.existsSync(sourceUri.fsPath)) {

			vscode.window.showErrorMessage('The source ' + className + '.cpp already exists!');	
			return;
		}

		let headerContent = `#pragma once

class ClasName
{
	public:

};`;

		let sourceContent = '#include "ClasName.h"\n';

		headerContent = headerContent.replace('ClasName', className);
		sourceContent = sourceContent.replace('ClasName', className);

		await vscode.workspace.fs.writeFile(headerUri, Buffer.from(headerContent, 'utf8'));
		await vscode.workspace.fs.writeFile(sourceUri, Buffer.from(sourceContent, 'utf8'));

		vscode.window.showTextDocument(headerUri);
	});
	
	inputBox.show();
}

// The "Generate Projects" Command
export function generateProjects()  {
	
	let terminal = global.extension.getTerminal();

	terminal.sendText('NewWorldPlugin -q generate-projects');
	terminal.show();
}

// The "Build" Command
export function build() {

	let terminal = global.extension.getTerminal();

	terminal.sendText('NewWorldPlugin -q build');
	terminal.show();
}

export function createFont(path: string) {

	let terminal = global.extension.getTerminal();

	if (path === undefined) {
	
		vscode.window.showErrorMessage('Undefined file path!');	
		return;
	}
	
	let pathUri = vscode.Uri.parse(path).fsPath;

	terminal.sendText('NewWorldPlugin -q create-font \"' + pathUri + "\"");
	terminal.show();
}