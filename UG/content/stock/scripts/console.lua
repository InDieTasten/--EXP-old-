function onLoad()

end
function onUnload()

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