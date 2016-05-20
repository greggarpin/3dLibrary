const char* SimpleVertexShader = STRINGIFY(

attribute vec4 Position;
attribute vec4 SourceColor;
varying vec4 DestinationColor;
uniform mat4 Projection;
uniform mat4 Modelview;
                                           
void main(void)
{
    DestinationColor = SourceColor;
    if (true)
    {
        gl_Position = Projection * Modelview * Position;
        return;
    }
    vec4 legit = Projection*vec4(.5,-1.938,-1.659,1);
    legit /= legit.w;
//    gl_Position = Projection * Modelview * Position;
    if (Position.x > 0.0)
        legit.x -= .1;
    else
        legit.x += .1;
    if (Position.y > 0.0)
        legit.y -= .1;
    else
        legit.y += .1;
    gl_Position = legit;
});

