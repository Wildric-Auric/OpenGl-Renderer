#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
void main()
{
    gl_Position = position;
};
#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
//Uniform
uniform vec4 u_Color;
uniform vec2 u_Res;
uniform float u_Time;
//Local
float c1 = 2.;
float c2 = 0.;
float c3 = 0.9;
//void main() {
//	vec2 uv = gl_FragCoord.xy / u_Res;
//	//gl_FragColor = vec4(uv.x, uv.y, 0.0, 1.0);
//	for (int i = 0; i < uv)
//	gl_FragColor = vec4(col, 1.0);
//}
//


//Gradient
//void main() {
//	vec2 uv = gl_FragCoord.xy / u_Res;
//	//gl_FragColor = vec4(uv.x, uv.y, 0.0, 1.0);
//	vec3 col = vec3(uv.x*c1, uv.x*c2, uv.x*c3);
//	gl_FragColor = vec4(col, 1.0);
//}




//Epilepsia
//void main() {
//	vec2 uv = gl_FragCoord.xy / u_Res;
//	float c1 = 2.;
//	float c2 = 0.;
//	float c3 = 0.9;
//	gl_FragColor = vec4(abs(cos(uv.x * c1 * u_Time * 10.)), uv.x * c2, uv.x * c3, 1);
//}




////LSD POV

void main() {
    vec2 coord = 6.0 * gl_FragCoord.xy / u_Res;

    for (int n = 1; n < 8; n++) {
        float i = float(n);
        coord += vec2(0.7 / i * sin(i * coord.y + u_Time + 0.3 * i) + 0.8, 0.4 / i * sin(coord.x + u_Time + 0.3 * i) + 1.6);
    }

    coord *= vec2(0.7 / sin(coord.y + u_Time + 0.3) + 0.8, 0.4 / sin(coord.x + u_Time + 0.3) + 1.6);

    vec3 color = vec3(0.5 * sin(coord.x) + 0.5, 0.5 * sin(coord.y) + 0.5, sin(coord.x + coord.y));

    gl_FragColor = vec4(color, 1.0);
}



