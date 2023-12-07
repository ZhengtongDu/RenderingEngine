#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 lightPosition;
    vec3 lightDirection;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // point light
    float constant;
    float linear;
    float quadratic;

    // flash light
    vec3 flashlightPosition;
    vec3 flashlightDirection;
    float cutOff;
    float outerCutOff;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;
// casterType == 1 ---> point light
// casterType == 2 ---> parallel light
// casterType == 3 ---> flash light
uniform int casterType;

void main()
{
    // preprocessing
    // diffuse coeffecients
    vec3 norm = normalize(Normal);
    vec3 lightDir;
    vec3 position;
    vec3 direction;
    vec3 result = vec3(1.0f);
    float attenuation;
    if (casterType == 1) {
        position = light.lightPosition;
        direction = light.lightDirection;
        lightDir = normalize(position - FragPos);
        float distance = length(position - FragPos);
        attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        result *= attenuation;
    }
    else if (casterType == 2) {
        position = light.lightPosition;
        direction = light.lightDirection;
        lightDir = normalize(-direction);
    }
    else if (casterType == 3) {
        position = light.flashlightPosition;
        direction = light.flashlightDirection;
        lightDir = normalize(position - FragPos);
        float distance = length(position - FragPos);
        attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        result *= attenuation;
    }
    float diff = max(dot(norm, lightDir), 0.0f);
    // specular coeffecients
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // ambient light
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    // diffuse light
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    // specular light
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    if(casterType == 3) {
        float theta = dot(lightDir, normalize(-direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
        diffuse *= intensity;
        specular *= intensity;
    }
    result *= (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0f);
}
