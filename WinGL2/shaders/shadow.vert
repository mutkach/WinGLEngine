uniform mat4 shadowMatTransform;


void main(void)
{
        
        gl_Position = shadowMatTransform * gl_Vertex;
}