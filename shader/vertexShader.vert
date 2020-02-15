#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 normal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;
out vec2 texCoord;
out vec3 FragPos;
out vec3 Normal;
void main(){
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
    vertexColor = vec4(color.rgb, 1.0f);
    texCoord = aTexCoord;
    FragPos = vec3(modelMat * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(modelMat))) * normal;
}