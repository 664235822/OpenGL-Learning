#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
uniform sampler2D ourTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
out vec4 FragColor;
void main(){
    FragColor = vec4(objColor * ambientColor, 1.0f) * texture(ourTexture, texCoord);
}