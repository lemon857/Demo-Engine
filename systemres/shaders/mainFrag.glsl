#version 330 core
out vec4 color;


void main()
{    
    color = vec4(vec3(exp(-gl_FragCoord.w)), 1);
}  