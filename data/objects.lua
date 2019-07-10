--------------------------------------------------------------------------
-- START PROGRAMATICALLY-CREATED OBJECT CODE
__luma_system.containers.object_ids = {
    objTest = 1,
    objTest2 = 2,
}
__luma_system.containers.sprite_ids = {
    sprTest = 1,
}
__luma_system.containers.object_code[1] = function()
    x = math.random(356)
    y = math.random(356)
    
    function init()
        printf("init! x[%i] y[%i] (objTest)", x, y)
    end
    
    function update()
        printf("update! x[%i] y[%i]", x, y)
    end
    
    function draw()
        print("drawing!!")
        -- draw_sprite(sprTest)
    end
end
__luma_system.containers.object_code[2] = function()

end
-- END PROGRAMATICALLY-CREATED OBJECT CODE
--------------------------------------------------------------------------

-- test data
lua_objects_check = 345897