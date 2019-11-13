#ifndef OBJECTS_CLASS_
#define OBJECTS_CLASS_

#include "global.h"

class objects
{
private:
    std::vector<int> displayLists;
    int listCount;

public:
    objects();
    int newObject(int type, GLuint texture, float height, float base);
};

#endif /* OBJECTS_CLASS_ */
