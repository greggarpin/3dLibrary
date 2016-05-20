const char* SelectionVertexShader = STRINGIFY(

attribute vec4 Position;
varying vec4 DestinationColor;
uniform vec4 SelectionColor;
uniform mat4 Projection;
uniform mat4 Modelview;
                                              
void main(void)
{
    DestinationColor = SelectionColor;
    gl_Position = Projection * Modelview * Position;
});