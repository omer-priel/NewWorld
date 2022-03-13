#shader vertex
#version 330 core

layout(location = 0) in vec4 postion;
layout(location = 1) in vec2 textureCood;

out vec2 v_TextureCood;

uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = postion;
    v_TextureCood = textureCood;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCood;

uniform sampler2D u_Texture;

void main()
{
	color = textureColor texture(u_Texture, v_TextureCood);
};