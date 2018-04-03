----------------------------------
-- scene2.lua
-- Simple scene definition
-- Vahid Kazemi - 2005
----------------------------------

cameraLookAt(0,0,0,   0,0,1,  1,0,0);
setHDR(16, 0.5, 1);
--setSuperSample(1);

-- Create Lights ---------------------------------------------

obj = createSphere(5,-2,-2, 0);
setEmissive(obj, 0.5);
setLight(obj);

obj = createSphere(5,2,-2, 0);
setEmissive(obj, 0.5);
setLight(obj);

-- Create Objects -------------------------------------------

obj = createPlane(1, 0, -0.5, -10);
setSpecular(obj, 0.5);
setTexture(obj, "image", "textures/wood.tga");
setMapping(obj, "cube", 0.1, 0.1, 0.1);

obj = createPlane(-0.5, 0, -1, -10);
setDiffuse(obj, 0);
setReflection(obj, 1);

obj = createSphere(0,-2,5, 2);
setColor(obj, 1.0, 0.1, 0.1);
setReflection(obj, 0.7);
setSpecular(obj,0.5);

obj = createSphere(-0.5,2,5, 2.0);
setColor(obj, 0.5, 0.5, 1.0);
setDiffuse(obj, 0.5);
setReflection(obj, 0.4);
setSpecular(obj,0.5);

render("output.jpg")
