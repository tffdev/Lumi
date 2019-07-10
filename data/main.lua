-- Containers and Standard Library
--------------------------------------------------------
-- Warning that using functionality contained in __luma_system is NOT safe for users.
-- System functionality is contained in __luma_system to make sure users don't accidentally call
-- these functions resulting in incorrect game behaviour etc.
__luma_system = {}
__luma_system.containers = {}
__luma_system.containers.instances = {}
__luma_system.containers.object_ids = {}
__luma_system.containers.sprite_ids = {}
__luma_system.containers.instances_buffer = {}

-- prepare global scope.
setmetatable(_G, {
    __index = function(table, key)
        -- if the variable is an object reference
        if(table._G.__luma_system.containers.object_ids[key] ~= nil) then
            return table._G.__luma_system.containers.object_ids[key]
        end
        -- if the variable is a sprite reference
        if(table._G.__luma_system.containers.sprite_ids[key] ~= nil) then
            return table._G.__luma_system.containers.sprite_ids[key]
        end
        return nil
    end,
    __newindex = function(table, key, value)
        if(table._G.__luma_system.containers.object_ids[key] ~= nil or 
           table._G.__luma_system.containers.sprite_ids[key] ~= nil) then
            error("Cannot overwrite constant \"" .. tostring(key) .. "\".")
        end
        rawset(table, key, value)
    end
})

-- C function placeholders
function __luma_system:run_object_code() end

function __luma_system:create_new_instance_environment(parent)
    new_env = parent or {}
    -- all properly created environments will have
    -- correct access to the original global environment
    new_env._G = _G

    return _G.setmetatable(new_env, {
        __index = function(table, key)
            -- if in the original global scope (functions like print etc)
            if(table._G[key] ~= nil) then
                return table._G[key]
            end
            -- not in any scopes, doesn't exist
            return nil
        end
    })
end

-- do something in a temporary first-class environment
function __luma_system:process_in_environment(env, func)
    _ENV = env
    func()
    _ENV = _G
end

-- create a new object environment
-- run object's "init" function within environment
-- push into instance buffer
function __luma_system:instance_create(id, x, y)
    local x = x or 0
    local y = y or 0
    -- error checking
    if(id == nil) then
        print("can't create instance")
        return false
    end

    -- create instance
    local new_object = __luma_system:create_new_instance_environment()
    -- add all default attributes to object here! like x and y coords etc
    __luma_system:process_in_environment(new_object, function()
        __luma_system.containers.object_code[id]()
        __luma_system:try_running(init)
    end)
    table.insert(__luma_system.containers.instances_buffer, new_object)
    return true
end

function __luma_system:push_instances()
    -- v contains table of instances
    for i, v in ipairs(__luma_system.containers.instances_buffer) do
        table.insert(__luma_system.containers.instances, v)
    end
    __luma_system.containers.instances_buffer = {}
end

function __luma_system:try_running(func)
    if(func ~= nil and type(func) == "function") then func() end
end

function __luma_system:process_update()
    __luma_system:push_instances()
    -- update loop!
    for j, v in ipairs(__luma_system.containers.instances) do
        __luma_system:process_in_environment(__luma_system.containers.instances[j], function()
            __luma_system:try_running(update)
        end)
    end
end

function __luma_system:process_draw()
     -- draw loop!
    for j, v in ipairs(__luma_system.containers.instances) do
        __luma_system:process_in_environment(__luma_system.containers.instances[j], function()
            __luma_system:try_running(draw)
        end)
    end
end

-- PUBLIC standard library
function instance_create(...)
    return __luma_system:instance_create(...)
end

function printf(str, ...)
    print(string.format(str, ...))
end

-- test data
lua_main_check = 983652