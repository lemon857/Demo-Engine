#version 330 core
layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_coords;

uniform vec2 textureScale;

out vec2 TextureCoords;

//uniform mat4 view_projectionMat;
void main() 
{
	gl_Position = vec4(vertex_position, 0.0, 1);
	TextureCoords = textureScale * tex_coords;
}