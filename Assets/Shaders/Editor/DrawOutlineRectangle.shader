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
layout (triangle_strip, max_vertices = 24) out;

uniform float u_LineWidth;
uniform mat4 u_ProjectionMatrix;

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

void main() {

	float x1 = gl_in[0].gl_Position.x;
	float y1 = gl_in[0].gl_Position.y;
	float x2 = gl_in[1].gl_Position.x;
	float y2 = gl_in[1].gl_Position.y;

	vec4 lineWidth = vec4(u_LineWidth, u_LineWidth, 0.0, 1.0) * u_ProjectionMatrix;

	// line 1
	drawRectangle(x1, y1, x2, y1 + lineWidth.y);

	// line 2
	drawRectangle(x2, y1, x2 - lineWidth.x, y2);

	// line 3
	drawRectangle(x2, y2, x1, y2 + lineWidth.y);

	// line 4
	drawRectangle(x1, y2, x1 - lineWidth.x, y1);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
};