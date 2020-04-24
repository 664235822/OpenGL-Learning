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

struct LightDirectional{
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
};

struct LightPoint{
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
};

struct LightSpot{
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
    float cosInnerPhy;
    float cosOuterPhy;
};

uniform Material material;
uniform LightDirectional lightDirectional;
uniform LightPoint lightPoint0;
uniform LightPoint lightPoint1;
uniform LightPoint lightPoint2;
uniform LightPoint lightPoint3;
uniform LightSpot lightSpot;

uniform float constant;
uniform float linear;
uniform float quadratic;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 cameraPos;

out vec4 FragColor;

vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera) {
    float diffIntensity = max(dot(light.dirToLight, uNormal), 0);
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, texCoord).rgb;;

    vec3 R = normalize(reflect(-light.dirToLight, uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
    vec3 specColor = specIntensity * light.color * texture(material.specular, texCoord).rgb;

    vec3 result = diffColor + specColor;
    return result;
}

vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera) {
    float dist = length(light.pos - FragPos);
    float attenuation = 1/(constant + linear * dist + quadratic * (dist * dist));

    float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, texCoord).rgb;

    vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
    vec3 specColor = specIntensity * light.color * texture(material.specular, texCoord).rgb;

    vec3 result = diffColor + specColor;
    return result;
}

vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera) {
    float dist = length(light.pos - FragPos);
    float attenuation = 1/(constant + linear * dist + quadratic * (dist * dist));
    float spotRatio;
    float CosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);

    if (CosTheta > light.cosInnerPhy) {
        spotRatio = 1.0f;
    } else if (CosTheta > light.cosOuterPhy) {
        spotRatio = (CosTheta - light.cosOuterPhy) / (light.cosInnerPhy - light.cosOuterPhy);
    } else {
        spotRatio = 0;
    }

    float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation * CosTheta;
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, texCoord).rgb;

    vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation * CosTheta;
    vec3 specColor = specIntensity * light.color * texture(material.specular, texCoord).rgb;

    vec3 result = diffColor + specColor;
    return result;
}

void main(){
    vec3 finalResult = vec3(0, 0, 0);
    vec3 uNormal = normalize(Normal);
    vec3 dirToCamera = normalize(cameraPos - FragPos);

    finalResult += CalcLightDirectional(lightDirectional, uNormal, dirToCamera);
    finalResult += CalcLightPoint(lightPoint0, uNormal, dirToCamera);
    finalResult += CalcLightPoint(lightPoint1, uNormal, dirToCamera);
    finalResult += CalcLightPoint(lightPoint2, uNormal, dirToCamera);
    finalResult += CalcLightPoint(lightPoint3, uNormal, dirToCamera);
    finalResult += CalcLightSpot(lightSpot, uNormal, dirToCamera);

    FragColor = vec4(finalResult, 1.0f);
}