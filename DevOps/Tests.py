import requests
import json
import git

from Scripts.Settings import Settings

gitSettings = Settings['Git']

repo = git.Repo()

print(f"Git Folder Path: {repo.git._working_dir}")  # Get Git Folder Path
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
# GitLab API: https://docs.gitlab.com/ee/api/commits.html
request_url = 'https://' + gitSettings['Server'] + '/api/v4/projects/' + gitSettings['ProjectID'] + '/repository/commits/' + repo.active_branch.name
res = requests.get(request_url)
if res.status_code != 200:
	print(f"The server {gitSettings['Server']} return status code: {res.status_code}")
else:
	res_object = json.loads(res.text)
	res_object = {
    	'id': res_object['id'],
    	'message': res_object['message'],
    	'author': res_object['author_name'],
    	'url': res_object['web_url']
	};
	print(res_object)
print(f"---------------------------------------------")
