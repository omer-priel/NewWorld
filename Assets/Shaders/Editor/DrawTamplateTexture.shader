#header
#version 330 core

uniform mat4 u_ProjectionMatrix;

uniform vec4 u_Color;

uniform vec2 u_TextureSize;
uniform sampler2D u_Texture;

#shader vertex

layout(location = 0) in vec4 postion;
layout(location = 1) in vec2 textureCood;

out DATA
{
    vec2 textureCood;
} vertex_out;

out vec2 v_TextureCood;

void main()
{
    gl_Position = u_ProjectionMatrix * postion;
    vertex_out.textureCood = textureCood / u_TextureSize;
};

#shader geometry
layout (lines) in;
layout (triangle_strip, max_vertices = 6) out;

in DATA
{
	vec2 textureCood;
} vertex_in[];

out DATA
{
	vec2 textureCood;
} vertex_out;

void main() {

	vec4 v1 = gl_in[0].gl_Position;
	vec4 v2 = gl_in[1].gl_Position;

	vec2 v2_TextureCood;

	// triangle 1
	gl_Position = vec4(v1.x, v1.y, 0.0, 1.0);
	vertex_out.textureCood = vertex_in[0].textureCood;
	EmitVertex();

	gl_Position = vec4(v2.x, v1.y, 0.0, 1.0);
	vertex_out.textureCood = vec2(vertex_in[1].textureCood.x, vertex_in[0].textureCood.y);
	EmitVertex();

	gl_Position = vec4(v2.x, v2.y, 0.0, 1.0);
	vertex_out.textureCood = vertex_in[1].textureCood;
	EmitVertex();
    
	EndPrimitive();

	// triangle 2
	gl_Position = vec4(v1.x, v1.y, 0.0, 1.0);
	vertex_out.textureCood = vertex_in[0].textureCood;
	EmitVertex();

	gl_Position = vec4(v1.x, v2.y, 0.0, 1.0);
	vertex_out.textureCood = vec2(vertex_in[0].textureCood.x, vertex_in[1].textureCood.y);
	EmitVertex();

	gl_Position = vec4(v2.x, v2.y, 0.0, 1.0);
	vertex_out.textureCood = vertex_in[1].textureCood;
	EmitVertex();
    
	EndPrimitive();
};

#shader fragment

layout(location = 0) out vec4 color;

in DATA
{
	vec2 textureCood;
} vertex_in;

void main()
{	
	vec4 textureColor = texture(u_Texture, vertex_in.textureCood);
	color = vec4(u_Color.r, u_Color.g, u_Color.b, u_Color.a * textureColor.a);
};