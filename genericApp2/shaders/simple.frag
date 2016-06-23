const char *SimpleFragmentShader = STRINGIFY(

varying lowp vec4 DestinationColor;
varying lowp vec3 DestinationNormal;
varying lowp float bRenderLighting;
uniform lowp vec3 LightPosition;
uniform lowp vec3 LightColor;

void main(void)
{
    if (bRenderLighting == 0.0)
    {
        gl_FragColor = DestinationColor;
    }
    else
    {
        /*
gl_FragColor = vec4((DestinationNormal + vec3(1.0,1.0,1.0))/2.0, 1.0);
/*/
// TODO:: Normals are still not coming through right
        lowp float diffuseStrength = 0.33;
        lowp float lightContrib = max(0.0, dot(LightPosition, DestinationNormal));
        lowp vec3 ambient = vec3((1.0 - diffuseStrength) * DestinationColor);
        lowp vec3 diffuse = lightContrib * LightColor * diffuseStrength;
        gl_FragColor = vec4(ambient + diffuse, 1.0);
//*/
    }
}
);