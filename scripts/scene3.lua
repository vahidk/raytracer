----------------------------------
-- scene3.lua
-- Simple scene definition
-- Vahid Kazemi - 2005
----------------------------------

setHDR(64, 0.5, 1.5);
cameraLookAt(0,-0.1,0,   1,0,0,  0,0,1);
cameraPerspective(2, 1, 1, 1000);

setSuperSample(1);

-- Create Lights ---------------------------------------------

obj = createSphere(-2,-2,5, 0);
setEmissive(obj, 0.5);
setLight(obj);

obj = createSphere(-2,2,5, 0);
setEmissive(obj, 0.5);
setLight(obj);

obj = createSphere(5,0,-5, 0);
setEmissive(obj, 0.5);
setLight(obj);

-- Create Objects -------------------------------------------

obj = createPlane(-1, 0, 0, -10);
setColor(obj, 0.5, 0.5, 0.3);
setDiffuse(obj, 1);

obj = createPlane(1, 0, 0, -10);
setColor(obj, 0.5, 0.5, 0.3);
setDiffuse(obj, 0.5);
setReflection(obj, 0.5);

obj = createPlane(0, 0, 1, -10);
setColor(obj, 1, 1, 1);
setTexture(obj, "image", "textures/floor.tga");
setMapping(obj, "cube", 0.3, 0.3, 0.3);

obj = createPlane(0, 0, -1, -10);
setColor(obj, 1, 1, 1);
setTexture(obj, "image", "textures/floor.tga");
setMapping(obj, "cube", 0.3, 0.3, 0.3);

obj = createPlane(0, 1, 0, -10);
setColor(obj, 0.8, 0.8, 0.5);
setDiffuse(obj, 0.5);

obj = createPlane(0, -1, 0, -10);
setColor(obj, 0.8, 0.8, 0.5);
setDiffuse(obj, 0.5);

obj = createSphere(3,0,0, 2);
setDiffuse(obj, 0);
setReflection(obj, 1);
setSpecular(obj,0.5);

render("output.jpg")