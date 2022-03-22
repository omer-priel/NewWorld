#header
#version 330 core

uniform mat4 u_ProjectionMatrix;

uniform float u_AngleStart;
uniform float u_AngleLength;
uniform vec2 u_Radius;
uniform int u_VerticesCount;
uniform float u_LineWidth;

uniform vec4 u_Color;

#shader vertex

layout(location = 0) in vec4 postion;

void main()
{
    gl_Position = u_ProjectionMatrix * postion;
};

#shader geometry

layout (points) in;
layout (triangle_strip, max_vertices = 255) out;

void drawQuadrate(vec2 v1, vec2 v2, vec2 v3, vec2 v4)
{
	// triangle 1
	gl_Position = vec4(v1.x, v1.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(v2.x, v2.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(v3.x, v3.y, 0.0, 1.0);
	EmitVertex();
    
	EndPrimitive();

	// triangle 2
	gl_Position = vec4(v1.x, v1.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(v4.x, v4.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(v3.x, v3.y, 0.0, 1.0);
	EmitVertex();
    
    EndPrimitive();
}

void main() {

	vec2 center = vec2(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y);
	
	vec4 lineWidth = u_ProjectionMatrix * vec4(u_LineWidth, u_LineWidth, 0.0, 1.0);
	lineWidth = lineWidth + 1;

	vec4 radius = u_ProjectionMatrix * vec4(u_Radius.x, u_Radius.y, 0.0, 1.0);
	radius = radius + 1;

	vec4 radiusIn = radius - lineWidth;

	int verticesCount = u_VerticesCount;

	float angle = u_AngleStart;
	float angleStep = u_AngleLength / verticesCount;

	// draw arc
	vec2 backPointOut = vec2(center.x + radius.x * sin(angle), center.y + radius.y * cos(angle));
	vec2 backPointIn = vec2(center.x + radiusIn.x * sin(angle), center.y + radiusIn.y * cos(angle));

	for (int i = 0; i < verticesCount; i++)
	{
		angle += angleStep;

		vec2 nowPointOut = vec2(center.x + radius.x * sin(angle), center.y + radius.y * cos(angle));
		vec2 nowPointIn = vec2(center.x + radiusIn.x * sin(angle), center.y + radiusIn.y * cos(angle));		
		drawQuadrate(backPointOut, nowPointOut, nowPointIn, backPointIn);

		backPointOut = nowPointOut;
		backPointIn = nowPointIn;
	}
};

#shader fragment

layout(location = 0) out vec4 color;

void main()
{
    color = u_Color;
};