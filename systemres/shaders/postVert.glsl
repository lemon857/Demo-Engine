#version 330 core
layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_coords;

out vec2 TextureCoords;

//uniform mat4 view_projectionMat;
void main() 
{
	TextureCoords = tex_coords;
	gl_Position = vec4(vertex_position, 0.0, 1);
}