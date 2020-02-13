#version 330 core
in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;
uniform sampler2D ourTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
out vec4 FragColor;
void main(){
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = dot(lightDir, Normal) * lightColor;
    FragColor = vec4((ambientColor + diffuse) * objColor, 1.0f) * texture(ourTexture, texCoord);
}