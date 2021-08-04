import subprocess
import json

from Scripts.Settings import Settings

gitSettings = Settings['Git'];

# GitLab API: https://docs.gitlab.com/ee/api/commits.html

# for /f "tokens=* USEBACKQ" %%i IN (`git rev-parse --short HEAD`) DO (SET gitID=%%i )
# ECHO %gitID%
# set barnch=master

command = '@echo off & for /f "tokens=* USEBACKQ" %i in (`git rev-parse --short HEAD`) do echo %%i'
stream = p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
(output, err) = p.communicate()
p.wait()

id = str(output[1:-1])
print(id)

gitBarnch="master";
command = '@echo off & curl "https://' + gitSettings['Server'] + '/api/v4/projects/' + gitSettings['ProjectID'] + '/repository/commits/"' + gitBarnch;
stream = p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
(output, err) = p.communicate()
p.wait()

output = json.loads(output)

data = {
    'id': output['short_id'],
    'message': output['message'],
    'author': output['author_name'],
    'url': output['web_url']
};

print(data)