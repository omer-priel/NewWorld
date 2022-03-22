# Shaders
Shaders saved in binary file (.nws), but created from text file (.shader)

## Shader pre-complie file Format (.shader)
#header
code ...
#shader vertex
code ...
#shader geometry
code ...
#shader fragment
code ...

* Under #header whill be the version and the uniforms

## New World Shader (.nws)
Custom file that save the shader as binary for New World Engine
To create this file use "NewWorldPlugin create-shader" command


### Format:
list of ShaderParts
* int ShaderPartLength
* bytes[ShaderPartLength] ShaderPartCode

### Shader Part Types
#shader vertex
#shader fragment