-- this is the [[UG]]-Console Interpreter

function onLoad()
	print("console.lua loaded :)")
end
function onUnload()
	print("console.lua unloaded :(")
end
function onSoftEvent(...)
	mytab = {...}
	for k,v in pairs(mytab) do
		print(k,v,"\n")
	end
end