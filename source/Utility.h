#ifndef __BEA_UTILITY_
#define __BEA_UTILITY_

#include "math.h"
#include "Phoenix.h"

namespace bea{

inline const phoenix::Color hsv( float h, float s, float v, float a = 1.0f ){
	phoenix::Color c;
	float i = floor(h * 6.0f);
	float f = h * 6.0f - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch( int(i) % 6 ){
		case 0: c = phoenix::Color(v*255,t*255,p*255,a*255); break;
		case 1: c = phoenix::Color(q*255,v*255,p*255,a*255); break;
		case 2: c = phoenix::Color(p*255,v*255,t*255,a*255); break;
		case 3: c = phoenix::Color(p*255,q*255,v*255,a*255); break;
		case 4: c = phoenix::Color(t*255,p*255,v*255,a*255); break;
		case 5: c = phoenix::Color(v*255,p*255,q*255,a*255); break;
	}

	return c;
}


}; //namespace bea
#endif