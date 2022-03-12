#shader vertex
#version 330 core

layout(location = 0) in vec4 postion;

void main()
{
    gl_Position = postion;
};

#shader geometry
#version 330 core
layout (lines) in;
layout (triangle_strip, max_vertices = 6) out;

uniform mat4 u_ProjectionMatrix;
uniform float u_LineWidth;

void drawQuadrate(vec2 v1, vec2 v2, vec2 v3, vec2 v4)
{
	// triangle 1
	gl_Position = u_ProjectionMatrix * vec4(v1.x, v1.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = u_ProjectionMatrix * vec4(v2.x, v2.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = u_ProjectionMatrix * vec4(v3.x, v3.y, 0.0, 1.0);
	EmitVertex();
    
	EndPrimitive();

	// triangle 2
	gl_Position = u_ProjectionMatrix * vec4(v1.x, v1.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = u_ProjectionMatrix * vec4(v4.x, v4.y, 0.0, 1.0);
	EmitVertex();

	gl_Position = u_ProjectionMatrix * vec4(v3.x, v3.y, 0.0, 1.0);
	EmitVertex();
    
    EndPrimitive();
}

void main() {

	vec2 v1 = vec2(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y);
	vec2 v2 = vec2(gl_in[1].gl_Position.x, gl_in[1].gl_Position.y);

	float thickness = u_LineWidth / 2;

	float len = sqrt((v2.y - v1.y)*(v2.y - v1.y) + (v2.x - v1.x)*(v2.x - v1.x));

	float xt =  (thickness/len) * (v2.y - v1.y);
	float yt =  (thickness/len) * (v2.x - v1.x);

	// draw line
	drawQuadrate(vec2(v1.x-xt, v1.y+yt), vec2(v2.x-xt, v2.y+yt), vec2(v2.x+xt, v2.y-yt), vec2(v1.x+xt, v1.y-yt));
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
};