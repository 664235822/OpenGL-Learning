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

struct LightSpot{
    float cosInnerPhy;
    float cosOuterPhy;
};

uniform Material material;
uniform LightPoint lightPoint;
uniform LightSpot lightSpot;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;
void main(){
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDirUniform, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);

    float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
    vec3 specular = texture(material.specular, texCoord).rgb * specularAmount * lightColor;

    vec3 ambient = texture(material.diffuse, texCoord).rgb * ambientColor;

    vec3 diffuse = texture(material.diffuse, texCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;

    float dist = length(lightPos - FragPos);
    float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * dist + lightPoint.quadratic * (dist * dist));

    float cosTheta = dot(normalize(FragPos - lightPos), -1 * lightDirUniform);

    //平行光源
    //FragColor = vec4((ambient + diffuse + specular) * objColor, 1.0f);

    //点光源
    //FragColor = vec4((ambient + (diffuse + specular) * attenuation) * objColor, 1.0f);

    //聚光源
    float spotRatio;
    if (cosTheta > lightSpot.cosInnerPhy){
        spotRatio = 1.0f;
    } else if (cosTheta > lightSpot.cosOuterPhy){
        spotRatio = 1.0f -  (cosTheta - lightSpot.cosInnerPhy) / (lightSpot.cosOuterPhy - lightSpot.cosInnerPhy);
    } else {
        spotRatio = 0;
    }
    FragColor = vec4((ambient + (diffuse + specular) * spotRatio) * objColor, 1.0f);

}