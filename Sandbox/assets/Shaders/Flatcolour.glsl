#type vertex	
#version 430 core
layout(location = 0) in vec3 a_Pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.0);
}

#type pixel
#version 430 core

uniform vec4 u_Colour = vec4(0.6, 0.1, 0.5, 1.0);

out vec4 color;

void main() {
	color = u_Colour;
}