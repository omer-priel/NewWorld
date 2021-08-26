// Utilities - Utilities class

import global = require('./global');

// Print log
export function log(message?: any, ...optionalParams: any[]) {
    
	console.log(global.extension.title + ": " + message);
}

// Print object members
export function dir(obj: any) {
    
	log("dir");
    console.dir(obj);
}