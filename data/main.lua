-- Containers and Standard Library
--------------------------------------------------------
-- Warning that using functionality contained in __lumi_system is NOT safe for users.
-- System functionality is contained in __lumi_system to make sure users don't accidentally call
-- these functions resulting in incorrect game behaviour etc.
__lumi_system = {}
__lumi_system.containers = {}
__lumi_system.containers.instances = {}
__lumi_system.containers.instances_buffer = {}

-- C function placeholders
function __lumi_system:get_asset_id(name) end

-- prepare global scope.
setmetatable(_G, {
    __index = function(table, key)
        -- if the variable is an asset reference contained in any of the attached databases
        local id = table._G.__lumi_system:get_asset_id(key)
        if(id ~= nil) then return id end
        return nil
    end,
    __newindex = function(table, key, value)
        if(table._G.__lumi_system:get_asset_id(key) ~= nil) then
            error("[LUMA] Cannot overwrite constant \"" .. tostring(key) .. "\".")
        end
        rawset(table, key, value)
    end
})

function __lumi_system:create_new_instance_environment(parent)
    local new_env = parent or {}
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
        end,
        __newindex = function(table, key, value)
            if(table._G[key] ~= nil) then
                table._G[key] = value
                return
            end
            rawset(table, key, value)
        end
    })
end

function __lumi_system:clear_all_instances()
    for i,v in ipairs(__lumi_system.containers.instances) do
        if __lumi_system.containers.instances[i].persistent ~= true then
            table.remove(__lumi_system.containers.instances, i)
        end
        if __lumi_system.containers.instances_buffer[i].persistent ~= true then
            table.remove(__lumi_system.containers.instances_buffer, i)
        end
    end
end

function __lumi_system:instance_create(id, x, y)
    local instance = __lumi_system:create_new_instance_environment()
    instance.id = id
    instance.x = x
    instance.y = y
    __lumi_system:process_in_environment(__lumi_system.containers.object_code[id+1], instance)
    __lumi_system:process_in_environment(instance.init, instance)
    table.insert(__lumi_system.containers.instances_buffer, instance)
end

function __lumi_system:push_instances()
    -- v contains table of instances
    for i, v in ipairs(__lumi_system.containers.instances_buffer) do
        table.insert(__lumi_system.containers.instances, v)
    end
    __lumi_system.containers.instances_buffer = {}
end

function __lumi_system:try_running(func)
    if(func ~= nil and type(func) == "function") then 
        func()
        return true
    end
    return false
end

function __lumi_system:process_draw()
    -- draw loop!
    for j, v in ipairs(__lumi_system.containers.instances) do
        __lumi_system:process_in_environment(__lumi_system.containers.instances[j].draw, __lumi_system.containers.instances[j])
    end
end

function __lumi_system:process_update()
    __lumi_system:push_instances()
    -- update loop!
    for j, v in ipairs(__lumi_system.containers.instances) do
        __lumi_system:process_in_environment(__lumi_system.containers.instances[j].update, __lumi_system.containers.instances[j])
    end
end

-- PUBLIC standard library
function instance_create(id, x, y)
    local x = x or 0
    local y = y or 0
    return __lumi_system:instance_create(id, x, y)
end

function printf(str, ...)
    print(string.format(str, ...))
end

-- globals
camera_x = 10
camera_y = 10

-- test data
___lua_main_check = 983652
