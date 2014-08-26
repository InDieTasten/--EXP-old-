function onLoad()

end
function onUnload()

end
function runCommand(cmd)
	print("Command issued: ", cmd)
	parts = {}
	for w in cmd:gmatch("%S+") do parts:insert(w) end
	for k,v in pairs(parts) do
		print("p",k,": ",v)
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
		if(e[2] == "$_consoleMenu.input") then
			pushTask("textbox_clear","$_consoleMenu.input")
			status, err = pcall(runCommand, e[3])
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