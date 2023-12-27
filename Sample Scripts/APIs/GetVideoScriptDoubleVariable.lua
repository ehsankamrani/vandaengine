--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoscriptdoublevariable/

--script name is GetVideoScriptDoubleVariable.lua attached a to game object such as light
return_value = 0.0

function Init()
	return_value = GetVideoScriptDoubleVariable("video1", "a")
end

function Update()

end
