 #version 120
 #define PI (3.1415926536)
 #define TWO_PI (6.2831853072)

 uniform sampler2DRect xyzMap;
 uniform sampler2DRect normalMap;
 uniform sampler2DRect confidenceMap;

uniform float elapsedTime;
uniform float soundVolume;
uniform int effectType;
uniform float effectValue1;
uniform float effectValue2;
uniform vec2 effectValue3;

const vec4 on = vec4(1.);
const vec4 off = vec4(vec3(0.), 0.1);
const vec2 resolution = vec2(1280,800);

float volumeSum = 0.0;

vec2 rotate(vec2 position, float amount) {
	mat2 rotation = mat2(
                         vec2( cos(amount),  sin(amount)),
                         vec2(-sin(amount),  cos(amount))
                         );
    return rotation * position;
}

float rings(vec2 p) {
    return sin(length(p)*1);
}
vec2 rand(vec2 pos) {
    return
    fract(
          (
           pow(
               pos+2.0,
               pos.yx+2.0
               )*22222.0
           )
          );
}
vec2 rand2(vec2 pos) {
    return rand(rand(pos));
}

void main() {
	vec2 overallOffset = vec2(0);//+vec2(floor( sin(elapsedTime*1)*10) ,0);
	vec4 curSample = texture2DRect(xyzMap, gl_TexCoord[0].st+overallOffset);
	vec4 curSampleNormal = texture2DRect(normalMap, gl_TexCoord[0].st+overallOffset);
	vec4 curSampleConfidence = texture2DRect(confidenceMap, gl_TexCoord[0].st+overallOffset);
	
	vec3 position = curSample.xyz;  //0~1が有効範囲
	vec3 normalDir = curSampleNormal.xyz;
	float confidence = curSampleConfidence.x;
	float present = curSample.a;
    
	if(position.z < 0) return;
    float b = soundVolume*0.9+.1;
    if(effectType == 0){
        if(normalDir.z < 0.5){
            float spacing = sin(elapsedTime) * .8 + 1;
            vec2 offset = rotate(vec2(1, 0), .6 * elapsedTime);
            float result = length(mod(position.xy + offset, spacing) * 2 - spacing / 2);
            gl_FragColor = (result < spacing / 2) ? on : off;
        }
    }else if(effectType == 1){
        gl_FragColor = (mod(position.x*sin(elapsedTime/1000), 10.0)>5.0) && (mod(position.y*sin(elapsedTime/1000), 10.0)>5.0)?vec4(vec3(1.), 1):off;
    }else if(effectType == 2){
        float b = soundVolume*0.7+.3;
        gl_FragColor = mod(position.xy[0]*100/sin(elapsedTime/100)/sin(elapsedTime), 10.0)>5.0?vec4(vec3(1.), b):off;
    }else if(effectType == 3){
        float b = soundVolume*0.7+.3;
        volumeSum += soundVolume;
        gl_FragColor = vec4(vec3(rings(position.xy*mod(sin(elapsedTime/10)*cos(volumeSum/10),100000)*100*cos(volumeSum)*cos(volumeSum))),b);
    }else if(effectType == 4){
        if( (position.x > effectValue3[0] && position.y > effectValue3[1]) || (position.x>0 && position.y>0 && position.x < effectValue3[0] && position.y < effectValue3[1]) ) {
            gl_FragColor = vec4(vec3(rand2(position.xy*sin(elapsedTime)).x),1);
        }
    }else if(effectType == 5){
        //         && mod(position.y*300,effectValue3[1]*effectValue2*20)>effectValue2*10
        float dx = mod(position.x*300,effectValue3[0]*effectValue2*10);
        float dy = mod(position.y*300,effectValue3[1]*effectValue2*10);
        float thresh = effectValue2*5;
        if(dx<thresh && dx > 0 && dy<thresh && dy > 0){
//            gl_FragColor = vec4(vec3(1,0,1),1);
            gl_FragColor = vec4(vec3(rand2(position.xy*sin(elapsedTime)).xyx/2+.5),1);
        }else{
            gl_FragColor = vec4(vec3(rand2(position.xy*sin(elapsedTime)).xyx/2+.5),.1);
        }
    }else if(effectType == 6){
        gl_FragColor = vec4(vec3(1,0,1),1);
    }else if(effectType == 7){
        gl_FragColor = vec4(vec3(1,1,1),1);
    }else if(effectType == 8){
        gl_FragColor = vec4(vec3(0,0,0),1);
    }
}

