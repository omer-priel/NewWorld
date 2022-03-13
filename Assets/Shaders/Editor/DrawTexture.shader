#shader vertex
#version 330 core

layout(location = 0) in vec4 postion;
layout(location = 1) in vec2 textureCood;

out vec2 v_textureCood;

uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * postion;
    v_textureCood = textureCood;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_textureCood;

in vec2 v_textureCood;

void main()
{
    color = texture(sampler2D(0), v_textureCood);
};