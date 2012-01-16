//
//  ofxBokeh.h
//
//
//  Created by Tim Scaffidi ( http://timothyscaffidi.com/ )
//
//  He share it on the openFrameworks forum here:
//  http://forum.openframeworks.cc/index.php/topic,8583.msg40032.html#msg40032
//

#ifndef OFXBOKEH 
#define OFXBOKEH

#include "ofxFXObject.h"
#include "ofxUnsharp.h"

class ofxBokeh : public ofxUnsharp {	
public:
    ofxBokeh(){
        passes = 3;
        internalFormat = GL_RGBA;
        
        // Fade constant
        value0 = 1.f;   
        
        // In this example the tex0 it´s more like a backbuffer 
        fragmentShader = "#version 120\n \
        #extension GL_ARB_texture_rectangle : enable\n \
        \
        uniform sampler2DRect tex0;\
        uniform float value0;\
        \
        void main(void) {\
            \
            vec4 finalColor = vec4(0.0,0.0,0.0,1.0);\
            float weight = 0.;\
            int radius = int(value0);\
            \
            for(int x = radius * -1 ; x < radius; x++) {\
                for(int y = radius * -1; y < radius; y++){\
                    \
                    vec2 coord = gl_TexCoord[0].xy + vec2(x,y);\
                    \
                    if(distance(coord, gl_TexCoord[0].xy) < float(radius)){\
                        vec4 texel = texture2DRect(tex0, coord);\
                        float w = length(texel.rgb)+ 0.1;\
                        weight += w;\
                        finalColor += texel * w;\
                    }\
                }\
            }\
            \
            gl_FragColor = finalColor/weight;\
        }";  
    };
    
	void setRadius(float _radius) { value0 = _radius;};
};

#endif
