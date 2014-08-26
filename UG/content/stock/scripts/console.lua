function onLoad()

end
function onUnload()

end
function runCommand(cmd)
	print("Command issued: ", cmd)
	parts = {}
	for w in cmd:gmatch("%S+") do table.insert(parts,w) end
	for k,v in pairs(parts) do
		print("p",k,": ",v)
	end
	--- Interpretation
	if(parts[1] == "create") then
		if(parts[2] == "task") then

		end
		if(parts[2] == "event") then

		end
	end


end
function onSoftEvent(...)
	print("---e")
	for k,v in pairs({...}) do
		print(type(v).." "..tostring(k)..": "..tostring(v))
	end
	print("---e")
	e = {...}
	if e[1] == "textbox_submit" then
		if(e[2] == "$_codeIDE.main") then
			pushTask("textbox_clear","$_codeIDE.main")
			status, err = pcall(runCommand, e[3])
			if(not status) then
				print("[Error] "..tostring(err))
			end
		end
	end
end
function onTask(...)
	print("---t")
	for k,v in pairs({...}) do
		print(type(v).." "..tostring(k)..": "..tostring(v))
	end
	print("---t")
end