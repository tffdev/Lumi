-- LUMA GENERATED CODE -------------------------------------
__luma_system.containers.object_code = {}
__luma_system.containers.object_code[1] = function()
    x = math.random(10)
    y = math.random(10)
    index = 0

    function update()
        if(key_down("up")) then y = y - 1 end
        if(key_down("down")) then y = y + 1 end
        if(key_down("left")) then x = x - 1 end
        if(key_down("right")) then x = x + 1 end
        if(key_pressed("e")) then 
            audio_play(sfxCoin, false) 
        end
        if(key_pressed("f")) then
            audio_stop(musicWater)
        end
        index = index + 0.1
    end

    function draw()
        draw_sprite(playerRun, index, x, y)
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