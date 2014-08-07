-- this is the [[UG]]-Console Interpreter

local function printTable(table, i)
	if(i == nil) then i = 0 end
	if (i > 10) then return end
	for k,v in pairs(table) do
		print(string.rep(" ",i*2),type(v), ": " ,k)
		if(type(v) == "table") then
			if(k ~= "_G" and k ~= "package") then
				printTable(v, i+1)
			end
		end
	end
end

function onLoad()
	print("console.lua loaded")
	--printTable(_G)
end
function onUnload()
	print("console.lua unloaded")
end
function onSoftEvent(...)
	e = {...}
	if e[1] == "textbox_submit" then
		if(e[2] == "$_consoleMenu.input") then
			interpret(e[3])
		end
	end
end

function interpret(cmd)
	
end