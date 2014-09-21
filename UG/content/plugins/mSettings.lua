local function genMenu()
	menu = "settings"
	pushTask("gui","menu","add", menu)
	pushTask("gui","menu", "access", menu, "property", "x", "set", "50")
	pushTask("gui","menu", "access", menu, "property", "y", "set", "50")
	pushTask("gui","menu", "access", menu, "property", "width", "set", "300")
	pushTask("gui","menu", "access", menu, "property", "height", "set", "400")
	pushTask("gui","menu", "access", menu, "property", "widthT", "set", "300")
	pushTask("gui","menu", "access", menu, "property", "heightT", "set", tostring(21*30+10))
	pushTask("gui","menu", "access", menu, "property", "visible", "set", "true")
	pushTask("gui","menu", "access", menu, "property", "scrollable", "set", "true")
	pushTask("gui","menu", "access", menu, "property", "title", "set", "--[[ SETTINGS ]]--")
end
local function label(id,y,text)
	menu = "settings"
	pushTask("gui","menu", "access", menu, "element", "add", id)
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "type", "set", "label")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "x", "set", "10")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "y", "set", tostring(y))
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "displayText", "set", tostring(text))
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "textColorA", "set", "#00FF00FF")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "textColorB", "set", "#404040F4")
end
local function slider(id,y,min,max,val)
	menu = "settings"
	pushTask("gui","menu", "access", menu, "element", "add", id)
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "type", "set", "horslider")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "x", "set", "150")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "y", "set", tostring(y))
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "width", "set", "130")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "height", "set", "16")
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "min", "set", tostring(min))
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "max", "set", tostring(max))
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "val", "set", tostring(val))
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "ratio", "set", tostring(1/2))
end
function onLoad() -- called right after the plugin has been loaded
	genMenu()
	for i = 1, 30, 1 do
		label("label"..tostring(i) , (i-1)*21+10,  "Label "..tostring(i)..":" ) slider("slider"..tostring(i) , (i-1)*21+10 , 1, 30, i)
	end

	pushTask("gui","menu", "access", "settings", "element", "list")

end
function onUnload() -- called right before your plugin gets overriden with nil
	pushTask("gui","menu","remove", "settings")
end

function onEvent(...) -- gets called when something happens
	
end
function onTask(...) -- gets called when something should happen
	
end
