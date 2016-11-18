/*-------------------
   axis_shader.vs
--------------------*/

#version 330 core

layout(location = 0) in vec3 axisPosition;
layout(location = 1) in vec3 axisColor;

out vec3 AxisColor;

void main()
{
gl_Position = vec4(axisPosition,1.0f);
AxisColor = axisColor;
}