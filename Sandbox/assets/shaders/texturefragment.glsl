#version 430 core

in vec2 v_Tex;

uniform sampler2D u_Texture;

out vec4 color;

void main() {
	vec4 col = texture(u_Texture, v_Tex);
	color = col;
}