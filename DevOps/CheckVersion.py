import subprocess
import json

command = '@echo off & for /f "tokens=* USEBACKQ" %i in (`git rev-parse --short HEAD`) do echo %%i'
stream = p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
(output, err) = p.communicate()
p.wait()

id = str(output[1:-1])
print(id)

command = '@echo off & curl "https://gitlab.com/api/v4/projects/28527190/repository/commits/master"';
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