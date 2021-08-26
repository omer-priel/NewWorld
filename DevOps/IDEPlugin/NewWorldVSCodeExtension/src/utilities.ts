// Utilities - Utilities class

import global = require('./global');

export function log(message?: any, ...optionalParams: any[]) {
    
	console.log(global.extension.title + ": " + message);
}

export function dir(obj: any) {
    
	log("dir");
    console.dir(obj);
}