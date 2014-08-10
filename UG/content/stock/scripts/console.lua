function onLoad()
end
function onUnload() end
function onSoftEvent(...)
	for k,v in pairs({...}) do
		print(type(v).." "..tostring(k)..": "..tostring(v))
	end
	e = {...}
	if e[1] == "textbox_submit" then
		if(e[2] == "$_consoleMenu.input") then
			--interpret(e[3])
		end
	end
end
function onTask(...)
	print("TASK DETECTED!")
end