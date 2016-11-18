/*-------------------
   axis_shader.frag
--------------------*/

#version 330 core

in vec3 AxisColor;
out vec4 color;

void main()
{
color = vec4(AxisColor,1.0f);
}