-- LUMA GENERATED CODE -------------------------------------
__luma_system.containers.object_code = {}
__luma_system.containers.object_code[1] = function()
    a = math.random(574)
    x = math.random(356)
    y = math.random(357)
    yspd = math.random(357)/90
    xspd = math.random(357)/90
    
    function update()
        y = y + yspd
        x = x + xspd
    end

    function draw()
        draw_square(x, y)
    end
end

__luma_system.containers.object_code[2] = function()
    x = 5
end

__luma_system.containers.object_code[3] = function()
    function init()
        print("[LUA] Hello, this is init from objTest3")
    end
end
-- END LUMA GENERATED CODE ---------------------------------