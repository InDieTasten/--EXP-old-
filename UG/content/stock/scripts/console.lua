-- this is the [[UG]]-Console Interpreter

function onLoad()
	print("console.lua loaded :)")
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
	print("/Soft-Event captured\\")
end