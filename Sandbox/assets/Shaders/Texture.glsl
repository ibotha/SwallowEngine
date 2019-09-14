#type vertex	
#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_Tex;

out vec2 v_Tex;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.0);
	v_Tex = a_Tex;
}

#type pixel
#version 330 core

in vec2 v_Tex;

uniform sampler2D u_Texture;

out vec4 color;

void main() {
	vec4 col = texture(u_Texture, v_Tex);
	color = col;
}