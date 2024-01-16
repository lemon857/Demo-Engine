#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform float layer_text;
uniform mat4 view_projectionMat;

void main()
{
    gl_Position = view_projectionMat * vec4(vertex.xy, layer_text, 1.0);
    TexCoords = vertex.zw;
}  