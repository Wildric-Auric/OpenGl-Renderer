//vertex shader
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 local;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 clip;
uniform int uNormalized;

out vec3 uv;
out vec3 uvs;
out vec3 oVertexColor;
out vec2 oTexCoord;


void main()
{
    if (uNormalized !=0) {
        gl_Position = proj * view * model* vec4(normalize((local*vec4(position, 1.0)).xyz),1.0);
    }
    else {
        gl_Position = proj * view * model * vec4(((local * vec4(position, 1.0)).xyz), 1.0);

    }

    uv = position;
    uvs = (vec4(position, 1.0)).xyz;

    oVertexColor = vertexColor;
    oTexCoord = texCoord;
};

//fragment shader
#version 330 core
in vec3 uv;
in vec3 oVertexColor;
in vec2 oTexCoord;
in vec3 uvs;

out vec4 FragColor;
uniform float uTime;
uniform sampler2D sampleTex;
uniform sampler2D sampleTex1;
uniform float uPredominance;
void main()
{
    vec3 white = vec3(1.0f, 1.0f, 1.0f);
    vec3 vercol = oVertexColor * 0.5 * (sin(uTime) + 1);
    //FragColor = vec4(vercol, 1.0);
    FragColor = mix(texture(sampleTex, oTexCoord), texture(sampleTex1, oTexCoord), uPredominance); //(1.0 - (uvs.z * 5))
}