#shader vertex
#version 330 core

layout(location = 0) in vec4 postion;

uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * postion;
};

#shader geometry
#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

void main() {

	for (int i = 0; i < 3; i++)
    {
    	gl_Position = gl_in[i].gl_Position;
		EmitVertex();
    }
    
    EndPrimitive();
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
};