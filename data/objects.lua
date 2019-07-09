--------------------------------------------------------------------------
-- START PROGRAMATICALLY-CREATED OBJECT CODE
__luma_system.containers.asset_ids = {
    objTest = 1,
    objTest2 = 2,
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
    end
end
__luma_system.containers.object_code[2] = function()

end
-- END PROGRAMATICALLY-CREATED OBJECT CODE
--------------------------------------------------------------------------

lua_objects_check = 345897