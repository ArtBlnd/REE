#ifndef _REE_OBJECT_
#define _REE_OBJECT_

/* REEObject Interface => Base Of REE Interfaces. */
INTERFACE REEObject
{
    /* Distroy Object */
    void Distroy();
    /* Initalize Object */
    void Initalize();
};

#define SAFE_DISTROY(object) if(object) object->Distroy()
#define SAFE_INITALIZE(object) if(object) object->Initalize()

#endif