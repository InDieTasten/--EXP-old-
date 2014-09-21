local function genMenu()
	menu = "settings"
	pushTask("gui","menu","add", menu)
	pushTask("gui","menu", "access", menu, "property", "x", "set", "50")
	pushTask("gui","menu", "access", menu, "property", "y", "set", "50")
	pushTask("gui","menu", "access", menu, "property", "width", "set", "300")
	pushTask("gui","menu", "access", menu, "property", "height", "set", "400")
	pushTask("gui","menu", "access", menu, "property", "widthT", "set", "300")
	pushTask("gui","menu", "access", menu, "property", "heightT", "set", "400")
	pushTask("gui","menu", "access", menu, "property", "visible", "set", "true")
	pushTask("gui","menu", "access", menu, "property", "scrollable", "set", "false")
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
	pushTask("gui","menu", "access", menu, "element", "access", id, "property", "textColorB", "set", "#202020F0")
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
	label("label1" , 1*18,  "Label 1:" ) slider("slider1" , 1*18 , 10, 200, 64)
	label("label2" , 2*18,  "Label 2:" ) slider("slider2" , 2*18 , 10, 200, 64)
	label("label3" , 3*18,  "Label 3:" ) slider("slider3" , 3*18 , 10, 200, 64)
	label("label4" , 4*18,  "Label 4:" ) slider("slider4" , 4*18 , 10, 200, 64)
	label("label5" , 5*18,  "Label 5:" ) slider("slider5" , 5*18 , 10, 200, 64)
	label("label6" , 6*18,  "Label 6:" ) slider("slider6" , 6*18 , 10, 200, 64)
	label("label7" , 7*18,  "Label 7:" ) slider("slider7" , 7*18 , 10, 200, 64)
	label("label8" , 8*18,  "Label 8:" ) slider("slider8" , 8*18 , 10, 200, 64)
	label("label9" , 9*18,  "Label 9:" ) slider("slider9" , 9*18 , 10, 200, 64)
	label("label10", 10*18, "Label 10:") slider("slider10", 10*18, 10, 200, 64)
	label("label11", 11*18, "Label 11:") slider("slider11", 11*18, 10, 200, 64)
	label("label12", 12*18, "Label 12:") slider("slider12", 12*18, 10, 200, 64)
	label("label13", 13*18, "Label 13:") slider("slider13", 13*18, 10, 200, 64)
	label("label14", 14*18, "Label 14:") slider("slider14", 14*18, 10, 200, 64)
	label("label15", 15*18, "Label 15:") slider("slider15", 15*18, 10, 200, 64)

	pushTask("gui","menu", "access", "settings", "element", "list")

end
function onUnload() -- called right before your plugin gets overriden with nil
	pushTask("gui","menu","remove", "settings")
end

function onEvent(...) -- gets called when something happens
	
end
function onTask(...) -- gets called when something should happen
	
end
