#version 460 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 Normal;
// We take in the fragpos to calculate the angle with the lightPos
in vec3 FragPos;

void main()
{
    vec3 norm = normalize(Normal);
    // Take the vectors away from eachother and make it a unit vector
    // Magnitude and direction are not important
    vec3 lightDir = normalize(lightPos - FragPos);


    // get the max, if negative the norm and lightDir
    // it will be zero as we take the max between that and 0
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;


    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;


    vec3 result = ( ambient + diffuse ) * objectColor;
    FragColor = vec4(result, 1.0f);
}