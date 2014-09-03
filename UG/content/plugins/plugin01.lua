function onLoad() -- called right after the plugin has been loaded
	print("MEEEH was loaded :3")
end
function onUnload() -- called right before your plugin gets overriden with nil
	print("noooooh :(")
end

function onEvent(...) -- gets called when something happens
	e = {...} -- contains the event parts
	if(e[1] == "Hello") then
		if(e[2] == "World") then
			-- more on these can be read in our documentation
		end
	end
end
function onTask(...) -- gets called when something should happen
	t = {...}
	if(t[1] == "Hello") then
		if(t[2] == "World") then
			-- more on these can be read in our documentation
		end
	end
end
