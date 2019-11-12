#ifndef _POINT_CLASS
#define _POINT_CLASS

class point
{

public:
    float x, y, z;
    point(float fx, float fy, float fz){x=fx; y=fy; z=fz;}
    void setPoint(float newX, float newY, float newZ){x=newX; y=newY; z=newZ;}
};

#endif /*_POINT_CLASS*/
