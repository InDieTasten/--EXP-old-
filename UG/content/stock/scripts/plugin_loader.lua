function onLoad()
	print("plugin_loader.lua loaded")
	print("")
	print("looking for plugins...")
	for dir in io.popen([[dir "content/plugins" /b]]):lines() do print(dir) end
	print("")
	print("C Path: ", package.cpath)
end
function onUnload()
	print("plugin_loader.lua unloaded")
end
function onSoftEvent(...)
	
end