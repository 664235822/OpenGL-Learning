#version 330 core
in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct LightPoint{
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform LightPoint lightPoint;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;
void main(){
    float dist = length(lightPos - FragPos);
    float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * dist + lightPoint.quadratic * (dist * dist));

    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDirUniform, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);

    float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
    vec3 specular = texture(material.specular, texCoord).rgb * specularAmount * lightColor;

    vec3 ambient = texture(material.diffuse, texCoord).rgb * ambientColor;

    vec3 diffuse = texture(material.diffuse, texCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;

    FragColor = vec4((ambient + (diffuse + specular) * attenuation) * objColor, 1.0f);
}