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
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

void main() {

	gl_Position = vec4(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(gl_in[1].gl_Position.x, gl_in[0].gl_Position.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(gl_in[0].gl_Position.x, gl_in[1].gl_Position.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(gl_in[1].gl_Position.x, gl_in[1].gl_Position.y, 0.0, 1.0);
	EmitVertex();
    
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