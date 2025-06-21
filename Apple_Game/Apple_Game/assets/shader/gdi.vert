#version 150

uniform mat4 projMatrix, viewMatrix;

in vec4 position;

void main()
{
    gl_Position = projMatrix * viewMatrix * position;
}