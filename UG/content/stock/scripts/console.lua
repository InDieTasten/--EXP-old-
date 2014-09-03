function onHardLoad()

end
function onHardUnload()

end
local function runCommand(cmd)
	print("Command issued: ", cmd)
	parts = {}
	for w in cmd:gmatch("%S+") do table.insert(parts,w) end
	for k,v in pairs(parts) do
		print("p",k,": ",v)
	end
	--- Interpretation
	if(parts[1] == "create") then
		if(parts[2] == "task") then
			task = {}
			for i = 3, #parts do
				table.insert(task, parts[i])
			end
			pushTask(table.unpack(task))
		end
		if(parts[2] == "event") then
			event = {}
			for i = 3, #parts do
				table.insert(event, parts[i])
			end
			pushEvent(table.unpack(event))
		end
	end


end
function onHardEvent(...)
	print("+--event--")
	for k,v in pairs({...}) do
		print("I "..type(v).." "..tostring(k)..": "..tostring(v))
	end
	print("+---------")
	e = {...}
	if e[1] == "textbox_submit" then
		if(e[2] == "$_consoleMenu.input") then
			pushTask("textbox_clear","$_consoleMenu.input")
			status, err = pcall(runCommand, e[3])
			if(not status) then
				print("[Error] "..tostring(err))
			end
		end
	end
end
function onHardTask(...)
	print("+--task---")
	for k,v in pairs({...}) do
		print("I "..type(v).." "..tostring(k)..": "..tostring(v))
	end
	print("+---------")
end