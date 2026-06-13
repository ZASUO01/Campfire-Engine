#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTextureCoord;

uniform mat4 uViewProjection;
uniform mat4 uTransform;
uniform vec4 uTextureRect;

out vec2 fragTextureCoord;

void main(){
    gl_Position = uViewProjection * uTransform * vec4(inPos, 0.0, 1.0);
    fragTextureCoord = uTextureRect.xy + inTextureCoord * uTextureRect.zw;
}