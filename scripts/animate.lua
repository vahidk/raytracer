----------------------------------
-- animate.lua
-- Simple animation (requires ffmpeg)
-- Vahid Kazemi - 2005
----------------------------------

local vec3 = require "scripts/vec3"

os.execute("mkdir -p output")

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

setHDR(16, 0.5, 1);

from = vec3(0, -0.5, 0)
to = vec3(0, 0.5, 0.5)
num_frames = 300

for i = 1,num_frames do
    print("Rendering frame "..tostring(i))
    c = from:lerp(to, i / num_frames)
    cameraLookAt(c.x,c.y,c.z,   0,0,1,  1,0,0);
    render("output/data_" .. tostring(i) .. ".jpg")
end

os.execute("ffmpeg -r 60 -f image2 -s 1024x1024 -i output/data_%d.jpg -vcodec libx264 -crf 25  -pix_fmt yuv420p output.mp4")
