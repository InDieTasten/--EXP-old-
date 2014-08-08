local plugins = {}

function registerPlugin(path, name)
	if(type(name) ~= "string") then
		print("[Error] Plugin to be registered must name a string!")
		return
	end
	if(plugins[name]) then
		print("[Error] Plugin '"..name.."' already exists!")
		return
	end
	file, err = io.open(path)
	if(file) then
		file:close()
	else
		print("[Error] File '"..path.."' can not be accessed!")
		print("[Error] -> "..tostring(err))
	end
	plugins[name] = {["path"]=path, ["status"]="unloaded"}
	print("Plugin '"..name.."' successfully registered")
end
function loadPlugin(name)
	if(type(name) ~= "string") then
		print("[Error] Plugin to be loaded must name a string!")
		return
	end
	if(plugins[name]) then
		if(plugins[name].status == "unloaded") then
			--load it
			_G[name]=setmetatable({},{__index=_G})
		    local pl, err = loadfile(plugins[name].path,"bt",_G[name])
		    if(pl) then pl(); plugins[name].status = "loaded" else print(err) end
		else
			print("[Error] Plugin '"..name.."' already loaded!")
		end
	else
		print("[Error] Plugin '"..name.."' not found!")
	end
end
function unloadPlugin(name)
	if(type(name) ~= "string") then
		print("[Error] Plugin to be unloaded must name a string!")
		return
	end
	if(plugins[name]) then
		if(plugins[name].status == "loaded") then
			--unload it
			_G[name] = false
			plugins[name].status = "unloaded"
			print("Plugin '"..name.."' unloaded")
		else
			print("[Error] Plugin '"..name.."' already unloaded!")
		end
	else
		print("[Error] Plugin '"..name.."' not found!")
	end
end
function reloadPlugin(name)
	unloadPlugin(name)
	loadPlugin(name)
end
function checkPlugin(name)
	--
	--
end

--loadAPI("example.lua", "externAPI")
--print(externAPI.apiFunction("Test"))

function onLoad()
	for dir in io.popen([[dir "content/plugins" /b]]):lines() do
		registerPlugin("content/plugins/"..dir, string.sub(dir, 1, #dir-4))
	end
end
function onUnload()
	print("plugin_loader.lua unloaded")
end
function onSoftEvent(...)
	
end
