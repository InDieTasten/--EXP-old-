l = getLevel() --
	l["name"] = "name of the level"
	l["description"] = "description of the level"

setLevel(l)

syss = getSystems() --
	syss[1] = "systemID1"
	syss[2] = "systemID2"

selectSystem("systemID1") --

sys = getSystem("systemID1" || selected) --
	sys["id"] = "systemID1"
	sys["name"] = "systemName1"
	sys["description"] = "description of system"

setSystem(sys)
removeSystem()

objs = getObjects("systemID2" || selected) --
	objs[1] = "objName1"
	objs[2] = "objName2"

obj = getObject("systemID2" || selected, "objName1") --
	obj["name"] = "objName1"
	obj["description"] = "description of object"
	obj["rotation"] = 270
	obj["x"] = 0.5
	obj["y"] = 0.5
	obj["dx"] = 1.5
	obj["dy"] = 1.5
	obj["textureID"] = "$_missing"
	obj["mass"] = 20.4

setObject("systemID2" || selected, obj) --

removeObject("systemID2" || selected, obj || "objName1") 

x, y = getGameMouse() --

x, y = getGuiMouse()
