******************************************************************************
**
** VRTStudio (A Simple Raytracer)
**
** Created at: April 15th 2005
** Last Update: August 8th 2006
**
******************************************************************************

1. About VRT Studio

2. Scripting Commands

3. Contact

******************************************************************************

1. About VRT Studio:

VRTStudio is a simple IDE to create simple scenes and render it using
VRT's built-in raytracer engine.

VRT engine supports:

- Scene definition using Lua
- Different Lighting techniques like Ambient, Diffuse, Specular
- Raytraced shadows
- Reflection
- Refraction (Under development)
- Super-Sampling
- Linear Fog
- HDR (Under Development)
- Dual-Core CPUs
- Texture Generation (checker, wood, image (tga file))
- Texture Mapping (cube, sphere, cylinder)


******************************************************************************

2. Scripting Commands:

init(int width, int height);

clear();

render(string filename);

setGlobalAmbient(float ambient);

Object *createSphere(float cx, float cy, float cz, float radious);

Object *createPlane(float nx, float ny, float nd, float D);

void setColor(Object *obj, float r, float g, float b);

void setAmbient(Object *obj, float ambient);

void setDiffuse(Object *obj, float diffuse);

void setSpecular(Object *obj, float specular);

void setShininess(Object *obj, float shininess);

void setEmissive(Object *obj, float emissive);

void setLight(Object *obj);

void setReflection(Object *obj, float reflection);

void setRefraction(Object *obj, float refraction);

void setOpacity(Object *obj, float opacity);

void cameraPerspective(float fovy, float aspect, float znear);

void cameraLookAt(float px, float py, float pz, float vx, float vy, float vz, float ux, float uy, float uz);

void setMaxDepth(float maxDepth);

void setMaxDistance(float maxDistance);

void setFog(float r, float g, float b, float near, float far);

void setSuperSample(float value);

void setHDR(float blockSize, float exposure);

void setTexture(Object *obj, string textureType,...); // textureType currently can be "checker", "wood", "image"

void setMapping(Object *obj, string mappingType,...); // mappingType currently can be "cube", "sphere", "cylinder"

******************************************************************************


3. Contact:

Vahid Kazemi
vkazemi@gmail.com
