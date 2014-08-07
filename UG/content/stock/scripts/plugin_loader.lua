function loadAPI(f,g)
    _G[g]=setmetatable({},{__index=_G})
    loadfile(f,"bt",_G[g])()
end

--loadAPI("example.lua", "externAPI")
--print(externAPI.apiFunction("Test"))

function onLoad()
	print("plugin_loader.lua loaded")
	print("")
	print("looking for plugins...")
	for dir in io.popen([[dir "content/plugins" /b]]):lines() do
		print(dir)
	end
	loadAPI("content/plugins/plugin01.lua", "wurzel")
	wurzel.troll()
	print("")
	print("C Path: ", package.cpath)
end
function onUnload()
	print("plugin_loader.lua unloaded")
end
function onSoftEvent(...)
	
end
