import os
import sys
import json

solutionPath = None
Settings = None

def GetSubPath(filename):
	return f"{solutionPath}\{filename}"

def SetTitle(title):
	os.system(f'title {title}')

def PresToConinue():
	input("\nPress any key to continue . . . ")

def Init():
	global solutionPath
	global Settings
	solutionPath = os.getcwd()

	while not os.path.isdir(solutionPath + "/.git"):
		solutionPath = os.path.abspath(os.path.join(solutionPath, os.pardir))

	Settings = json.load(open(GetSubPath('DevOps\Scripts\Settings.json'),'r'))
	Settings['SolutionPath'] = solutionPath

	sys.path.append(GetSubPath('DevOps'))

Init()
Init = lambda: None