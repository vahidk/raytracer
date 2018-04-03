----------------------------------
-- scene1.lua
-- Simple scene definition
-- Vahid Kazemi - 2005
----------------------------------
cameraLookAt(0,0,0,   1,0,0,  0,0,1);

--setSuperSample(2);

setFog(0, 0, 0, 10, 20);

setHDR(64, 0.02, 0.5);

-- Create Lights ---------------------------------------------

obj = createSphere(-2,-2,5, 0);
setEmissive(obj, 0.5);
setDiffuse(obj,0);
setLight(obj);

obj = createSphere(-2,2,0, 0);
setEmissive(obj, 0.5);
setDiffuse(obj,0);
setLight(obj);

-- Create Objects --------------------------------------------

obj = createPlane(0, 0, 1, -2);
setColor(obj, 1, 1, 1);
setDiffuse(obj, 1);
setSpecular(obj, 0.4);
setReflection(obj, 0.6);
setTexture(obj, "checker");

obj = createPlane(0, 0, -1, -7);
setColor(obj, 1, 1, 0);
setDiffuse(obj, 1);
setSpecular(obj, 0.4);

obj = createSphere(5,-2.2,0, 2);
setColor(obj, 1.0, 1.0, 1.0);
setDiffuse(obj, 0.5);
setReflection(obj, 0.9);
setSpecular(obj, 1);
setShininess(obj, 32);

obj = createSphere(4.5,2,0, 2);
setColor(obj, 0.5, 1, 0.5);
setDiffuse(obj, 0.4);
setSpecular(obj, 1);
setShininess(obj, 32);
setReflection(obj, 0.7)

render("output.jpg")