----------------------------------
-- scene5.lua
-- Simple scene definition
-- Vahid Kazemi - 2005
----------------------------------

cameraLookAt(0,0,0,   1,0,0,  0,0,1);

-- Create Lights ---------------------------------------------

obj = createSphere(-2,-2,5, 0);
setEmissive(obj, 0.5);
setDiffuse(obj,0);
setLight(obj);

obj = createSphere(-2,2,5, 0);
setEmissive(obj, 0.5);
setDiffuse(obj,0);
setLight(obj);

-- Create Objects --------------------------------------------

obj = createPlane(0, 0, 1, -2);
setColor(obj, 0.5, 0.7, 1.0);
setDiffuse(obj, 0.5);
setSpecular(obj, 1);
setReflection(obj, 0.1);
setTexture(obj, "image", "textures/ground.tga");

for i=1, 9 do
   obj = createSphere(5,i-5,i*i*0.05, 1.5);
   setColor(obj, 0.5, 0.8, 0.5);
   setDiffuse(obj, 0.4);
   setReflection(obj, 0.5);
   setSpecular(obj, 1);
   setShininess(obj, 32);
end;

render("output.jpg")