#version 330 core
in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

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
    vec3 ambient = texture(material.diffuse, texCoord).rgb * ambientColor;
    vec3 specular = material.specular * speculatAmount * lightColor;
    vec3 diffuse = texture(material.diffuse, texCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;
    FragColor = vec4((ambient + diffuse + specular) * objColor, 1.0f);
}