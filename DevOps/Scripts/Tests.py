import sys
import os
import git

repo = git.Repo()

print(f"Solution Path: {repo.git._working_dir}")  # Get Solution folder
print(f"Active Branch: {repo.active_branch.name}") # Get current branch name
print(f"Commit ID    : {repo.head.object.hexsha}") # Get Commit ID
commit_message = repo.head.commit.message.split('\n')[0]
print(f"Last Commit  : '{commit_message}' | {repo.head.commit.author}") # Get Last Commit
print(f"---------------------------------------------")

def git_commited():
	modifided_files_count = len(repo.index.diff(None))
	untracked_files_count = len(repo.untracked_files)
	if untracked_files_count > 0 or modifided_files_count > 0:
		print(f"Exists {untracked_files_count} Untracked Files and {modifided_files_count} Modifided files")
		return False
	return True

git_commited()


print(f"---------------------------------------------")