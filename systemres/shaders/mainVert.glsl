#version 330
layout(location = 0) in vec3 vertex_position;

uniform mat4 view_projectionMat;

void main()
{
    gl_Position = view_projectionMat * vec4(vertex_position, 1.0);
}  