-- LUMA GENERATED CODE -------------------------------------
__luma_system.containers.object_code = {}
__luma_system.containers.object_code[1] = function()
    a = math.random(574)
    x = math.random(10)
    y = math.random(10)
    yspd = math.random(357)/300
    xspd = math.random(357)/300
    
    function update()
        y = y + yspd
        x = x + xspd
    end

    function draw()
        draw_sprite(playerRun, 0, x, y)
    end
end

__luma_system.containers.object_code[2] = function()
    x = 5
end

__luma_system.containers.object_code[3] = function()
    function init()
        print("[LUA] Hello, this is init from objTest3")
    end

    function draw()
        draw_sprite(sprCat, 0, 10, 10)
    end
end
-- END LUMA GENERATED CODE ---------------------------------