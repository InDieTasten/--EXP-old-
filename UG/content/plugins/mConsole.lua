function onLoad()

end
function onUnload()

end
local function runCommand(cmd)
	parts = {}
	for w in cmd:gmatch("%S+") do table.insert(parts,w) end

	--- Interpretation
    if(parts[1] == "t:") then
        task = {}
        for i = 2, #parts do
            table.insert(task, parts[i])
        end
        pushTask(table.unpack(task))
    end
    if(parts[1] == "e:") then
        event = {}
        for i = 2, #parts do
            table.insert(event, parts[i])
        end
        pushEvent(table.unpack(event))
    end
end
function onEvent(...)
	ev = ""
	for k,v in pairs({...}) do
		ev = ev.."  "..v
	end
	print("[Info] E: "..ev)
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
function onTask(...)
	ta = ""
	for k,v in pairs({...}) do
		ta = ta.."  "..v
	end
	print("[Info] T: "..ta)
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
