-- this is the [[UG]]-Console Interpreter

local function test()
	print("Normaler Text")
	print("Text und ",10)
	print("Text und ",10," und noch ein Text")
end

function onLoad()
	print("console.lua loaded :)")
	print("Test wird gestartet:\n\n")
	test()
end
function onUnload()
	print("console.lua unloaded :(")
end
function onSoftEvent(...)
	print("\\Soft-Event captured/")
	mytab = {...}
	for k,v in pairs(mytab) do
		print(tostring(k)..": "..tostring(v))
	end
	print("/Soft-Event captured\\", 5)
end