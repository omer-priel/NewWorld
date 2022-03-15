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
layout (triangle_strip, max_vertices = 255) out;

uniform mat4 u_ProjectionMatrix;
uniform float u_AngleStart;
uniform float u_AngleLength;
uniform vec2 u_Radius;
uniform int u_VerticesCount;

void drawTriangle(vec2 v1, vec2 v2, vec2 v3)
{
	gl_Position = vec4(v1.x, v1.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(v2.x, v2.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(v3.x, v3.y, 0.0, 1.0);
	EmitVertex();
    
	EndPrimitive();
}

void main() {

	vec2 center = vec2(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y);

	vec4 radius = u_ProjectionMatrix * vec4(u_Radius.x, u_Radius.y, 0.0, 1.0);
	radius = radius + 1;

	int verticesCount = u_VerticesCount;

	float angle = u_AngleStart;
	float angleStep = u_AngleLength / verticesCount;

	// draw arc
	vec2 backPoint = vec2(center.x + radius.x * sin(angle), center.y + radius.y * cos(angle));

	for (int i = 0; i < verticesCount; i++)
	{
		angle += angleStep;

		vec2 nowPoint = vec2(center.x + radius.x * sin(angle), center.y + radius.y * cos(angle));
		drawTriangle(center, backPoint, nowPoint);

		backPoint = nowPoint;
	}
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
};