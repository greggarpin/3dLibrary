const char* SimpleVertexShader = STRINGIFY(

attribute vec4 Position;
attribute vec4 SourceColor;
attribute vec3 Normal;
varying vec4 DestinationColor;
varying lowp vec3 DestinationNormal;
varying lowp float bRenderLighting;
uniform mat4 Projection;
uniform mat4 Modelview;
uniform vec4 SelectionId;
uniform mat4 NormalModelview;
uniform float EnableLighting;

void main(void)
{
////    gl_PointSize = 5.0;
    if (SelectionId != vec4(0,0,0,0) || EnableLighting == 0.0)
    {
        DestinationColor = SelectionId;
        bRenderLighting = 0.0;
    }
    else
    {
        DestinationColor = SourceColor;
        bRenderLighting = 1.0;

        mat3 normalModelView3 = mat3(NormalModelview);
        DestinationNormal = normalModelView3 * Normal;
    }
    // Looks like the normal is being rotated backwards relative to the object...
    gl_Position = Projection * Modelview * Position;
});

