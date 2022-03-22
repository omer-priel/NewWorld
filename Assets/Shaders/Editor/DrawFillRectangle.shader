#header
#version 460 core

uniform mat4 u_ProjectionMatrix;

uniform vec4 u_Color;

#shader vertex

layout(location = 0) in vec4 postion;

void main()
{
    gl_Position = u_ProjectionMatrix * postion;
};

#shader geometry

layout (lines) in;
layout (triangle_strip, max_vertices = 6) out;

void drawRectangle(float x1, float y1, float x2, float y2)
{
	// triangle 1
	gl_Position = vec4(x1, y1, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(x2, y1, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(x2, y2, 0.0, 1.0);
	EmitVertex();
    
	EndPrimitive();

	// triangle 2
	gl_Position = vec4(x1, y1, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(x1, y2, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(x2, y2, 0.0, 1.0);
	EmitVertex();
    
    EndPrimitive();
}

void main()
{
	drawRectangle(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y, gl_in[1].gl_Position.x, gl_in[1].gl_Position.y);
}

#shader fragment

layout(location = 0) out vec4 color;

void main()
{
    color = u_Color;
};