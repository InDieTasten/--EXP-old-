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

level = {
    name = "default",
    description = "decription of level 'default'",
    systems = {
        System1 = {
            ID = "System1",
            name = "System No. 1",
            description = "Description of system 'System1'",
            objects = {
                Object1 = {
                    ID = "Object1",
                    description = "description of object 'Object1'",
                    collidable = true,
                    flyByLocal = false,
                    ai = {"###AI-Behaviour scripts/options###"},
                    mass = 15,
                    position = {0, 0},
                    velocity = {1, 1},
                    gravity = true,
                    positionTarget = {100, 100},
                    rotation = 0,
                    rotationSpeed = 0,
                    shootdownTarget = "",
                    textureID = "missing",
                    visible = true,
                },
                Object2 = {
                    
                },
            },
        },
    },
    timestamp = "some weird time format"
}
menus = {
    menu1 = {
        ID = "Menu1",
        title = "My Menu #1",
        height = 200,
        width = 150,
        totalHeight = 200,
        totalWidth = 150,
        x = 10,
        y = 10,
        isActive = true,
        isHidden = false,
        scrollable = false,
        style = {
            background = {
                active = "#000000A0",
                inactive = "#00000010",
            },
            border = {
                active = "#00FF00A0",
                inactive = "#22222210",
            },
            title = {
                background = {
                    active = "#00000000",
                    inactive = "#00000000",
                },
                text = {
                    active = "#00000000",
                    inactive = "#00000000",
                },
            },
        },

        elements = {},
    },
}
dock = {}
bg = {}
fg = {}