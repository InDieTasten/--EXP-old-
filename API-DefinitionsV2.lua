l = getLevel() --
	l["name"] = "name of the level"
	l["description"] = "description of the level"

setLevel(l) --

syss = getSystems() --
	syss[1] = "systemID1"
	syss[2] = "systemID2"

selectSystem("systemID1") --

sys = getSystem() --
	sys["id"] = "systemID1"
	sys["name"] = "systemName1"
	sys["description"] = "description of system"

setSystem(sys) --

removeSystem() --

objs = getObjects() --
	objs[1] = "objName1"
	objs[2] = "objName2"

obj = getObject("objName1") --
	obj["name"] = "objName1"
	obj["description"] = "description of object"
	obj["rotation"] = 270
	obj["x"] = 0.5
	obj["y"] = 0.5
	obj["dx"] = 1.5
	obj["dy"] = 1.5
	obj["textureID"] = "$_missing"
	obj["mass"] = 20.4

setObject(obj) --

removeObject("objName1") --

x, y = getGameMouse() --

x, y = getGuiMouse() --

