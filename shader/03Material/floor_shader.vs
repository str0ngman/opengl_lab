/*-------------------
   floor_shader.vs
--------------------*/

#version 330 core

layout(location = 0) in vec3 floorPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
gl_Position = projection * view * model * vec4(floorPosition,1.0f);

}