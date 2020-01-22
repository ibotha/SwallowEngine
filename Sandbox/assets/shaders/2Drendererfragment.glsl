#version 430 core

uniform vec4 u_Colour;
uniform sampler2D u_Texture;
uniform float u_TillingFactor = 1.0;

out vec4 color;

in vec2 v_TexCoord;

void main() {
	color = texture(u_Texture, v_TexCoord * u_TillingFactor) * u_Colour;
}