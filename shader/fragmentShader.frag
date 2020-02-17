#version 330 core
in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

uniform sampler2D ourTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;
void main(){
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);
    float speculatAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
    vec3 ambient = material.ambient * ambientColor;
    vec3 specular = material.specular * speculatAmount * lightColor;
    vec3 diffuse = material.diffuse * max(dot(lightDir, Normal), 0) * lightColor;
    FragColor = vec4((ambient + diffuse * specular) * objColor, 1.0f) * texture(ourTexture, texCoord);
}