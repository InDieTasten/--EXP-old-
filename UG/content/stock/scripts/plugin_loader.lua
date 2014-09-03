local popen = io.popen
local open = io.open
local pushEvent = pushEvent
local pullEvent = pullEvent
local pushTask = pushTask
local pullTask = pullTask
io = nil

local plugins = {}


function onHardLoad()
	for dir in popen([[dir "content/plugins" /b]]):lines() do
		path = "content/plugins/"..dir
		name = string.sub(dir, 1, #dir-4)
		if(type(name) ~= "string") then
			print("[Error] Plugin to be registered must name a string!")
			return
		end
		if(plugins[name]) then
			print("[Error] Plugin '"..name.."' already exists!")
			return
		end
		file, err = open(path)
		if(file) then
			file:close()
		else
			print("[Error] File '"..path.."' can not be accessed!")
			print("[Error] -> "..tostring(err))
		end
		plugins[name] = {["path"]=path, ["status"]="unloaded"}
		print("[Info] Plugin '"..name.."' successfully registered")
	end
end
function onHardUnload()
	
end
function onHardEvent(...)
	for name, detail in pairs(plugins) do
		if(type(_G[name]) == "table") then
			if(type(_G[ name ][ "onEvent" ])=="function") then
				st, err = pcall(_G[ name ][ "onEvent" ], ...)
				if(not st) then print(err) end
			end
		end
	end
end
function onHardTask(...)
	cmd = {...}
	if(cmd[1] == "lua") then
		if(cmd[2] == "memory") then
			if(cmd[3] == "show") then
				print("Memory of plugin_loader: ",collectgarbage("count")," KB")
			end
			if(cmd[3] == "free") then
				collectgarbage("collect")
			end
		end
	end
	if(cmd[1] == "plugin") then
		if(cmd[2] == "call") then
			st, err = pcall(_G[ cmd[3] ][ cmd[4] ])
			if(not st) then print(err) end
		elseif(cmd[2] == "unload") then
			if(type(_G[ cmd[3] ]) == "table") then
				if(type(_G[ cmd[3] ][ "onUnload" ])=="function") then
					st, err = pcall(_G[ cmd[3] ][ "onUnload" ], ...)
					if(not st) then print(err) end
				end
			end
			_G[ cmd[3] ] = nil
		elseif(cmd[2] == "load") then
			_G[ cmd[3] ] = setmetatable({},{__index=_G})
			local pl, err = loadfile(plugins[ cmd[3] ].path,"bt",_G[ cmd[3] ])
			if(pl) then st, err = pcall(pl) if(not st) then print(err) end else print(err) end
			if(type(_G[ cmd[3] ]) == "table") then
				if(type(_G[ cmd[3] ][ "onLoad" ])=="function") then
					st, err = pcall(_G[ cmd[3] ][ "onLoad" ], ...)
					if(not st) then print(err) end
				end
			end
		elseif(cmd[2] == "reload") then
			if(type(_G[ cmd[3] ]) == "table") then
				if(type(_G[ cmd[3] ][ "onUnload" ])=="function") then
					st, err = pcall(_G[ cmd[3] ][ "onUnload" ], ...)
					if(not st) then print(err) end
				end
			end
			_G[ cmd[3] ] = nil
			_G[ cmd[3] ] = setmetatable({},{__index=_G})
			local pl, err = loadfile(plugins[ cmd[3] ].path,"bt",_G[ cmd[3] ])
			if(pl) then st, err = pcall(pl) if(not st) then print(err) end else print(err) end
			if(type(_G[ cmd[3] ]) == "table") then
				if(type(_G[ cmd[3] ][ "onLoad" ])=="function") then
					st, err = pcall(_G[ cmd[3] ][ "onLoad" ], ...)
					if(not st) then print(err) end
				end
			end
		end
	end
	for name, detail in pairs(plugins) do
		if(type(_G[name]) == "table") then
			if(type(_G[ name ][ "onTask" ])=="function") then
				st, err = pcall(_G[ name ][ "onTask" ], ...)
				if(not st) then print(err) end
			end
		end
	end
end
