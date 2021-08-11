import os
import sys

solutionPath = os.getcwd()

while not os.path.isdir(solutionPath + "/.git"):
	solutionPath = os.path.abspath(os.path.join(solutionPath, os.pardir))

sys.path.append(f"{solutionPath}\DevOps")

from Scripts.Settings import Settings

Settings['SolutionPath'] = solutionPath

def SetTitle(title):
	os.system(f'title {title}')

def PresToConinue():
	input("\nPress any key to continue . . . ")