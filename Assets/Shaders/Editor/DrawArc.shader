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
uniform float u_LineWidth;

void drawRectangle(vec2 v1, vec2 v2, vec2 v3, vec2 v4)
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
	lineWidth = (lineWidth + 1) / 2;

	vec4 radius = u_ProjectionMatrix * vec4(u_Radius.x, u_Radius.y, 0.0, 1.0);
	radius = (radius + 1) / 2;
	
	vec2 diameterOut = vec2(radius.x * 2, radius.y * 2);
	vec2 diameterIn = vec2((radius.x - lineWidth.x) * 2, (radius.y - lineWidth.y) * 2);

	int verticesCount = u_VerticesCount;

	float angle = u_AngleStart;
	float angleStep = u_AngleLength / verticesCount;

	verticesCount = 5;

	// test
	//drawRectangle(vec2(-0.1, -0.1), vec2(0.1, -0.1), vec2(0.1, 0.1), vec2(-0.1, 0.1));
	//drawRectangle(center.x, center.y, center.x + diameter.x + lineWidth.x, center.y + diameter.y + lineWidth.y);
	vec2 p1 = vec2(0.3 * sin(0),   0.3 * cos(0));
	vec2 p2 = vec2(0.2 * sin(0),   0.2 * cos(0));	
	vec2 p3 = vec2(0.3 * sin(0.5), 0.3 * cos(0.5));
	vec2 p4 = vec2(0.2 * sin(0.5), 0.2 * cos(0.5));		
	//drawRectangle(p1, p3, p4, p2); // work
		
	p1 = vec2(center.x + 0.3 * sin(0),   center.y + 0.3 * cos(0));
	p2 = vec2(center.x + 0.2 * sin(0),   center.y + 0.2 * cos(0));	
	p3 = vec2(center.x + 0.3 * sin(0.5), center.y + 0.3 * cos(0.5));
	p4 = vec2(center.x + 0.2 * sin(0.5), center.y + 0.2 * cos(0.5));
	//drawRectangle(p1, p3, p4, p2); // work

	p1 = vec2(center.x + diameterOut.x * sin(0),   center.y + diameterOut.x * cos(0));
	p2 = vec2(center.x + 0.1 * sin(0),   center.y + 0.1 * cos(0));	
	p3 = vec2(center.x + diameterOut.x * sin(0.5), center.y + diameterOut.x * cos(0.5));
	p4 = vec2(center.x + 0.1 * sin(0.5), center.y + 0.1 * cos(0.5));		
	//drawRectangle(p1, p3, p4, p2); // work

	p1 = vec2(center.x + diameterOut.x * sin(0),   center.y + diameterOut.y * cos(0));
	p2 = vec2(center.x + diameterIn.x * sin(0),   center.y + diameterIn.y * cos(0));	
	p3 = vec2(center.x + diameterOut.x * sin(0.5), center.y + diameterOut.y * cos(0.5));
	p4 = vec2(center.x + diameterIn.x * sin(0.5), center.y + diameterIn.y * cos(0.5));		
	//drawRectangle(p1, p3, p4, p2); // work

	p1 = vec2(center.x + diameterOut.x * sin(angle),   center.y + diameterOut.y * cos(angle));
	p2 = vec2(center.x + diameterIn.x * sin(angle),   center.y + diameterIn.y * cos(angle));	
	p3 = vec2(center.x + diameterOut.x * sin(angle + angleStep), center.y + diameterOut.y * cos(angle + angleStep));
	p4 = vec2(center.x + diameterIn.x * sin(angle + angleStep), center.y + diameterIn.y * cos(angle + angleStep));		
	//drawRectangle(p1, p3, p4, p2); // work

	// draw arc
	vec2 backPointOut = vec2(center.x + diameterOut.x * sin(angle), center.y + diameterOut.y * cos(angle));
	vec2 backPointIn = vec2(center.x + diameterIn.x * sin(angle), center.y + diameterIn.y * cos(angle));

	for (int i = 0; i < verticesCount; i++)
	{
		angle += angleStep;

		vec2 nowPointOut = vec2(center.x + diameterOut.x * sin(angle), center.y + diameterOut.y * cos(angle));
		vec2 nowPointIn = vec2(center.x + diameterIn.x * sin(angle), center.y + diameterIn.y * cos(angle));

		p1 = vec2(center.x + diameterOut.x * sin(angle),   center.y + diameterOut.y * cos(angle));
		p2 = vec2(center.x + diameterIn.x * sin(angle),   center.y + diameterIn.y * cos(angle));	
		p3 = vec2(center.x + diameterOut.x * sin(angle + angleStep), center.y + diameterOut.y * cos(angle + angleStep));
		p4 = vec2(center.x + diameterIn.x * sin(angle + angleStep), center.y + diameterIn.y * cos(angle + angleStep));		
		drawRectangle(p1, p3, p4, p2);

		backPointOut = nowPointOut;
		backPointIn = nowPointIn;
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