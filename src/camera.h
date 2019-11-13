#ifndef CAMERA_CLASS_
#define CAMERA_CLASS_

#include <windows.h>
#include <windowsx.h>

#include "global.h"
#include "point.h"

typedef struct tVector3					// expanded 3D vector struct
{
	tVector3() {}	// constructor
	tVector3 (float new_x, float new_y, float new_z) // initialize constructor
	{x = new_x; y = new_y; z = new_z;}
	// overload + operator so that we easier can add vectors
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator that we easier can subtract vectors
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator that we easier can multiply by scalars
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator that we easier can divide by a scalar
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}

	float x, y, z;						// 3D vector coordinates
}tVector3;

class camera
{
public:
    tVector3 mPos;
	tVector3 mView;
	tVector3 mUp;

	int mWindowWidth;
	int mWindowHeight;

	void moveMouse();

	void rotateView(float x, float y, float z);
	void moveCamera(float cameraspeed);
	void positionCamera(float pos_x, float pos_y,float pos_z,
		 				 float view_x, float view_y, float view_z,
						 float up_x,   float up_y,   float up_z);

};

#endif /* CAMERA_CLASS_ */
