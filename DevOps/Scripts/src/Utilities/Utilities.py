import os
import sys
import json
from types import SimpleNamespace

Settings = None

def GetSubPath(filename):
	return f"{Settings.SolutionPath}\{filename}"

def SetTitle(title):
	os.popen(f'title {title}').read()

def PresToConinue():
	input("\nPress any key to continue . . . ")

def ExitAction():
	PresToConinue()
	exit()

def Init():
	global Settings
	
	solutionPath = os.getcwd()

	while not os.path.isdir(solutionPath + "/.git"):
		solutionPath = os.path.abspath(os.path.join(solutionPath, os.pardir))
	
	file = open(f"{solutionPath}\DevOps\Scripts\Settings.json",'r')
	Settings = json.load(file, object_hook=lambda d: SimpleNamespace(**d))
	Settings.SolutionPath = solutionPath
	file.close()

	sys.path.append(GetSubPath('DevOps'))

Init()
Init = lambda: None