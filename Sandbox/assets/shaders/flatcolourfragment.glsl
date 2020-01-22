#version 430 core

uniform vec4 u_Colour = vec4(0.6, 0.1, 0.5, 1.0);

out vec4 color;

void main() {
	color = u_Colour;
}