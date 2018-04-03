----------------------------------
-- scene4.lua
-- Simple scene definition
-- Vahid Kazemi - 2005
----------------------------------

cameraLookAt(0,0,0,   1,0,0,  0,0,1);

-- Create Lights ---------------------------------------------

obj = createSphere(-2,-2,5, 0);
setDiffuse(obj,0);
setEmissive(obj, 0.5);
setLight(obj);

-- Create Objects -------------------------------------------

setMaxDepth(5);

obj = createPlane(-1, 0, 0, -10);
setColor(obj, 1, 0.5, 1);
setDiffuse(obj, 0.7);
setSpecular(obj, 0.5);
setShininess(obj,32);
setReflection(obj, 0.3);

obj = createPlane(1, 0, 0, -10);
setColor(obj, 1, 1, 0.0);
setDiffuse(obj, 0.7);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.3);

obj = createPlane(0, 0, 1, -10);
setColor(obj, 0.0, 1, 1);
setDiffuse(obj, 0.7);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.3);

obj = createPlane(0, 0, -1, -10);
setColor(obj, 1, 0.0, 0.5);
setDiffuse(obj, 0.7);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.3);

obj = createPlane(0, 1, 0, -10);
setColor(obj, 1, 0.5, 0.5);
setDiffuse(obj, 0.7);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.5);

obj = createPlane(0, -1, 0, -10);
setDiffuse(obj, 0.7);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.3);

obj = createSphere(5,-2,0, 2);
setColor(obj, 1.0, 0.1, 0.1);
setDiffuse(obj, 0.5);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.8);

obj = createSphere(5,2,-0.1, 2.0);
setColor(obj, 0.5, 0.5, 1.0);
setDiffuse(obj, 0.5);
setSpecular(obj, 1);
setShininess(obj,32);
setReflection(obj, 0.8);

render("output.jpg")