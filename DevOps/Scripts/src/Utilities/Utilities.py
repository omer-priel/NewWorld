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
    print("\nPress any key to continue . . .\n")
    input(" ")

def ExitAction():
	PresToConinue()
	exit()

def LoadJsonFile(path):
	file = open(path, 'r')
	obj = json.load(file, object_hook=lambda d: SimpleNamespace(**d))
	file.close()
	return obj


def CMD(command, show=False, workingDirectory=False):
	if (not workingDirectory):
		workingDirectory = Settings.SolutionPath

	os.chdir(workingDirectory)
	ret = os.popen(command).read()

	if (show):
		print(ret)
	return ret

def Init():
	global Settings
	
	solutionPath = os.getcwd()

	while not os.path.isdir(solutionPath + "/.git"):
		solutionPath = os.path.abspath(os.path.join(solutionPath, os.pardir))
	
	Settings = LoadJsonFile(f"{solutionPath}\DevOps\Scripts\Settings.json")
	Settings.SolutionPath = solutionPath

	sys.path.append(GetSubPath('DevOps'))

Init()
Init = lambda: None