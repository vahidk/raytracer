----------------------------------
-- basic.lua
-- Simple scene definition
-- Vahid Kazemi - 2005
----------------------------------
cameraLookAt(0,0,0,   1,0,0,  0,0,1);

obj = createSphere(-2,-2,5, 0);
setEmissive(obj, 1);
setLight(obj);

obj = createSphere(5,0,0, 3);

render("output.jpg")