#type vertex	
#version 430 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.0);
}

#type pixel
#version 430 core

uniform vec4 u_Colour;
uniform sampler2D u_Texture;

out vec4 color;

in vec2 v_TexCoord;

void main() {
	color = texture(u_Texture, v_TexCoord) * u_Colour;
}