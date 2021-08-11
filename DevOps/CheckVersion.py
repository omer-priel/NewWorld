# CheckVersion - Show Solution code version info

import Scripts.Utilities as Utilities

import requests
import json
import git

Utilities.SetTitle("Check Version")

gitSettings = Utilities.Settings['Git']

repo = git.Repo(Utilities.Settings['SolutionPath'])

commit_id = repo.head.object.hexsha

print(f"Active Branch: {repo.active_branch.name}")
commit_message = repo.head.commit.message.split('\n')[0]
print(f"Last Commit  : '{commit_message}' | {repo.head.commit.author}")

modifided_files_count = len(repo.index.diff(None))
untracked_files_count = len(repo.untracked_files)

git_commited = untracked_files_count == 0 and modifided_files_count == 0

if not git_commited:
	print(f"Exists {untracked_files_count} Untracked Files and {modifided_files_count} Modifided files.\n")

# GitLab API: https://docs.gitlab.com/ee/api/commits.html
request_url = 'https://' + gitSettings['Server'] + '/api/v4/projects/' + gitSettings['ProjectID'] + '/repository/commits/' + repo.active_branch.name
res = requests.get(request_url)

if res.status_code != 200:
	print(f"The server {gitSettings['Server']} return status code: {res.status_code}")
else:
	res_object = json.loads(res.text)
	res_object = {
		'id': res_object['id'],
		'message': res_object['message'].split('\n')[0],
		'author': res_object['author_name'],
		'url': res_object['web_url']
	}

	if git_commited and res_object['id'] == commit_id:
		print("The repository is uptodate\n")
	else:
		print("The repository is not uptodate!\n")
		print(f"Server Last Commit  : {res_object['message']} | {res_object['author']}")
	print(f"Commit URL: {res_object['url']}")

Utilities.PresToConinue()