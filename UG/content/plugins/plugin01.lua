function onLoad() -- called right after the plugin has been loaded
	print("Katze")
	pushTask("gui","menu","add","can")
	pushTask("gui","menu", "access", "can", "property", "x", "set", "50")
	pushTask("gui","menu", "access", "can", "property", "y", "set", "50")
	pushTask("gui","menu", "access", "can", "property", "width", "set", "200")
	pushTask("gui","menu", "access", "can", "property", "height", "set", "200")
	pushTask("gui","menu", "access", "can", "property", "visible", "set", "true")
	pushTask("gui","menu", "access", "can", "property", "title", "set", ".canvas-.test-")
	pushTask("gui","menu", "access", "can", "element", "add", "canvas")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "property", "type", "set", "canvas")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "property", "x", "set", "10")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "property", "y", "set", "10")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "property", "width", "set", "180")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "property", "height", "set", "180")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "action", "setFillColor", "#0000FFFF")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "action", "draw", "line", "0","0","800","600")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "action", "draw", "line", "0","600","800","0")
	pushTask("gui","menu", "access", "can", "element", "access", "canvas", "action", "display")
end
function onUnload() -- called right before your plugin gets overriden with nil
	pushTask("gui","menu","remove","can")
end

function onEvent(...) -- gets called when something happens
	e = {...} -- contains the event parts
	if(e[1] == "Hello") then
		if(e[2] == "World") then
			-- more on these can be read in our documentation
		end
	end
end
function onTask(...) -- gets called when something should happen
	t = {...}
	if(t[1] == "Hello") then
		if(t[2] == "World") then
			-- more on these can be read in our documentation
		end
	end
end
