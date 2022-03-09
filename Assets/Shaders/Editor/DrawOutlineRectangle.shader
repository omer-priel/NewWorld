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
layout (lines) in;
layout (line_strip, max_vertices = 8) out;

uniform uint u_LineWidth;

void drawLine(float x1, float y1, float x2, float y2)
{
		// line 1
	gl_Position = vec4(x1, y1, 0.0, 1.0);
    EmitVertex();

	gl_Position = vec4(x2, y2, 0.0, 1.0);
    EmitVertex();

	EndPrimitive();
}

void main() {

	// line 1
	drawLine(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y, gl_in[1].gl_Position.x, gl_in[0].gl_Position.y);

	// line 2
	drawLine(gl_in[1].gl_Position.x, gl_in[0].gl_Position.y, gl_in[1].gl_Position.x, gl_in[1].gl_Position.y);

	// line 3
	drawLine(gl_in[1].gl_Position.x, gl_in[1].gl_Position.y, gl_in[0].gl_Position.x, gl_in[1].gl_Position.y);

	// line 4
	drawLine(gl_in[0].gl_Position.x, gl_in[1].gl_Position.y, gl_in[0].gl_Position.x, gl_in[0].gl_Position.y);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
};