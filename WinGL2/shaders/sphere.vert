
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

in vec3 point;
in vec3 normal;
in vec2 texCoord;

void main(void)
{
        
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(point, 1.0);
}