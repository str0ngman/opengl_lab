#version 330 core
in vec2 TexCoord;
out vec4 color;
uniform sampler2d Texture1;
uniform sampler2d Texture2;

void main(){
color = mix(texture(Texture1, TexCoord),texture(Texture2,Texcoord),0.2);
}