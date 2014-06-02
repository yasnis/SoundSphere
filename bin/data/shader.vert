#version 120
// This is pass-through vertex shader.
uniform vec2 mouse; // getting cursor postion coordinate.
uniform float soundVolume;
uniform int time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


void main(){
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    
    gl_FrontColor = vec4(vec3(rand(gl_Vertex.xy)),1);
    
//    int l = int(pos[0]);
//    if(l%2)return;
//    pos[0]+(rand(gl_Vertex.xy)*2-1)*pos[0]
    float s = sin(time/100);
    vec4 p = vec4(pos[0]+(rand(gl_Vertex.xy))*pos[0]*soundVolume*s,pos[1]+(rand(gl_Vertex.xy))*pos[1]*soundVolume*s,pos[2]+(rand(gl_Vertex.xy))*pos[2]*soundVolume*s,pos[3]);
    gl_Position = p;
//    gl_Position = vec4(pos[0],pos[1],pos[2],pos[3]);
//	gl_FrontColor = gl_Color;
    
    gl_PointSize = 10;
}
