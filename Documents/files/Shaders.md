# Shaders
Shaders saved in binary file (.nws), but created from text file (.shader)

## Shader pre-complie file Format (.shader)
#shader vertex
code ...
#shader fragment
code ...

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