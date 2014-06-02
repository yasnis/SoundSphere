#version 120

uniform vec2 mouse; // getting cursor postion coordinate.

void main(){
	//this is the fragment shader
	//this is where the pixel level drawing happens
	//gl_FragCoord gives us the x and y of the current pixel its drawing
	
	//we grab the x and y and store them in an int
	float xVal = gl_FragCoord.x;
	float yVal = gl_FragCoord.y;
    
	gl_FragColor = gl_Color;
    
//	if(mouse.x > xVal){
//		gl_FragColor.a = 0.0;
//	}
}

