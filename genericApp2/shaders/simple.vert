const char* SimpleVertexShader = STRINGIFY(

attribute vec4 Position;
attribute vec4 SourceColor;
varying vec4 DestinationColor;
uniform mat4 Projection;
uniform mat4 Modelview;
uniform vec4 SelectionId;

void main(void)
{
    if (SelectionId != vec4(0,0,0,0))
        DestinationColor = SelectionId;
    else
        DestinationColor = SourceColor;

    vec4 ans = Projection * Modelview * Position;
    ans /= ans.w;
    gl_Position = ans;
    return;

    vec4 legit;

    if (Position == vec4(-0.5, -0.5, -0.5, 1))      legit = vec4(.166666, -.111111, .259259, 1);
    else if (Position == vec4( 0.5, -0.5, -0.5, 1)) legit = vec4(-.166666, -.111111, .259259, 1);
    else if (Position == vec4(-0.5,  0.5, -0.5, 1)) legit = vec4(.166666, .111111, .259259, 1);
    else if (Position == vec4( 0.5,  0.5, -0.5, 1)) legit = vec4(-.166666, .111111, .259259, 1);
    else if (Position == vec4(-0.5, -0.5,  0.5, 1)) legit = vec4( .1, -.0666666, -.3333333, 1);
    else if (Position == vec4( 0.5, -0.5,  0.5, 1)) legit = vec4(-.1, -.0666666, -.3333333, 1);
    else if (Position == vec4(-0.5,  0.5,  0.5, 1)) legit = vec4( .1, .0666666, -.3333333, 1);
    else if (Position == vec4( 0.5,  0.5,  0.5, 1)) legit = vec4(-.1, .0666666, -.3333333, 1);
    else
        legit = vec4(0,0,0,1);

    gl_Position = legit;
});

