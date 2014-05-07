 #version 120
 #define PI (3.1415926536)
 #define TWO_PI (6.2831853072)

 uniform sampler2DRect xyzMap;
 uniform sampler2DRect normalMap;
 uniform sampler2DRect confidenceMap;
 uniform float elapsedTime;

void main() {
	vec2 overallOffset = vec2(0)+vec2(floor( sin(elapsedTime*1)*10) ,0);
	vec4 curSample = texture2DRect(xyzMap, gl_TexCoord[0].st+overallOffset);
	vec4 curSampleNormal = texture2DRect(normalMap, gl_TexCoord[0].st+overallOffset);
	vec4 curSampleConfidence = texture2DRect(confidenceMap, gl_TexCoord[0].st+overallOffset);
	
	vec3 position = curSample.xyz;
	vec3 normalDir = curSampleNormal.xyz;
	float confidence = curSampleConfidence.x;
	float present = curSample.a;
//	float stages = 11.;
//	float stage = 7;//+mod(elapsedTime * .3, stages);

	gl_FragColor = vec4(0);

//	if(confidence < .1) {
//        gl_FragColor = vec4(0);
//    } else {
        gl_FragColor = vec4(vec3(mod(elapsedTime * 2 + length(position) * 1, 1) > .99 ? 1 : 0), 1);
//	}
//    gl_FragColor = vec4(vec3(mod(elapsedTime * 2 + length(position) * 1, 1) > .99 ? 1 : 0), 1);
}

