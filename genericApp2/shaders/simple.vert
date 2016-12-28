const char* SimpleVertexShader = STRINGIFY(

attribute vec4 Position;
attribute vec4 SourceColor;
attribute vec3 Normal;
attribute vec2 TextureCoord;
varying vec4 DestinationColor;
varying lowp vec3 DestinationNormal;
varying lowp vec2 DestinationTextureCoord;
uniform mat4 Projection;
uniform mat4 Modelview;
uniform vec4 SelectionId;
uniform mat4 NormalModelview;
uniform float EnableLighting;
uniform float EnableTexturing;

void main(void)
{
////    gl_PointSize = 5.0;
    if (SelectionId != vec4(0,0,0,0) || EnableLighting == 0.0)
    {
        DestinationColor = SelectionId;
    }
    else
    {
        DestinationColor = SourceColor;

        mat3 normalModelView3 = mat3(NormalModelview);
        DestinationNormal = normalModelView3 * Normal;
    }

    if (EnableTexturing == 1.0)
    {
        DestinationTextureCoord = TextureCoord;
    }

    gl_Position = Projection * Modelview * Position;
});

