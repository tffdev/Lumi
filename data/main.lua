-- Containers and Standard Library
--------------------------------------------------------
-- Warning that using functionality contained in __luma_system is NOT safe for users.
-- System functionality is contained in __luma_system to make sure users don't accidentally call
-- these functions resulting in incorrect game behaviour etc.
__luma_system = {}
__luma_system.containers = {}
__luma_system.containers.object_code = {}
__luma_system.containers.instances = {}
__luma_system.containers.instances_buffer = {}

-- C function placeholders
function __luma_system:get_object_id(name) end

-- prepare global scope.
setmetatable(_G, {
    __index = function(table, key)
        -- if the variable is an object reference
        local objid = table._G.__luma_system:get_object_id(key)
        if(objid ~= nil) then
            return objid
        end
        return nil
    end,
    __newindex = function(table, key, value)
        if(table._G.__luma_system:get_object_id(key) ~= nil) then
            error("Cannot overwrite constant \"" .. tostring(key) .. "\".")
        end
        rawset(table, key, value)
    end
})

function __luma_system:create_new_instance_environment(parent)
    new_env = parent or {}
    -- all properly created environments will have
    -- correct access to the original global environment
    new_env._G = _G
    table.insert(__luma_system.containers.instances_buffer, new_env)
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

function __luma_system:push_instances()
    -- v contains table of instances
    for i, v in ipairs(__luma_system.containers.instances_buffer) do
        table.insert(__luma_system.containers.instances, v)
    end
    __luma_system.containers.instances_buffer = {}
end

function __luma_system:try_running(func)
    if(func ~= nil and type(func) == "function") then 
        func()
        return true
    end
    return false
end

function __luma_system:process_draw()
    -- draw loop!
    for j, v in ipairs(__luma_system.containers.instances) do
        __luma_system:process_in_environment(__luma_system.containers.instances[j], function()
            if(not __luma_system:try_running(draw)) then
                draw_sprite(x, y, current_sprite)
            end
        end)
    end
end

function draw_sprite( ... )
    
end

-- PUBLIC standard library
function instance_create(id, x, y)
    local x = x or 0
    local y = y or 0
    return __luma_system:instance_create(id, x, y)
end

function printf(str, ...)
    print(string.format(str, ...))
end

-- test data
___lua_main_check = 983652