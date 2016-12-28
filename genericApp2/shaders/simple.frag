const char *SimpleFragmentShader = STRINGIFY(

varying lowp vec4 DestinationColor;
varying lowp vec3 DestinationNormal;
varying lowp vec2 DestinationTextureCoord;
uniform lowp vec3 LightPosition;
uniform lowp vec3 LightColor;
uniform highp float EnableTexturing;
uniform highp float EnableLighting;

uniform sampler2D Sampler;

void main(void)
{
    if (EnableLighting == 0.0)
    {
        gl_FragColor = DestinationColor;
    }
    else
    {
        lowp float diffuseStrength = 0.33;
        lowp float lightContrib = max(0.0, dot(LightPosition, DestinationNormal));
        lowp vec3 ambient = vec3((1.0 - diffuseStrength) * DestinationColor);
        lowp vec3 diffuse = lightContrib * LightColor * diffuseStrength;
        gl_FragColor = vec4(ambient + diffuse, 1.0);
    }
    if (EnableTexturing == 1.0)
    {
        gl_FragColor += texture2D(Sampler, DestinationTextureCoord);
    }
}
);