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
	cmd = {...}
	if(cmd[1] == "lua") then
		if(cmd[2] == "memory") then
			if(cmd[3] == "show") then
				print("Memory of console: ", collectgarbage("count")," KB")
			end
			if(cmd[3] == "free") then
				tmp = collectgarbage("count")
				collectgarbage("collect")
				print("Free'd ",tmp-collectgarbage("count")," KB of Mem in console")
			end
		end
	end
	if(cmd[1] == "console") then
		if(cmd[2] == "run") then
			script = ""
			for i = 3, #cmd do
				script = script.." "..cmd[i]
			end
			print("Running following chunk:")
			print(script)
			ch, err = load(script)
			if(ch) then
				st, err = pcall(ch)
				if(not st) then print("[Error] ", err) end
			else
				print("[Error] ", err)
			end
		end
	end
end