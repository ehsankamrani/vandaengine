--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoscriptstringvariable/

--script name is GetVideoScriptStringVariable.lua attached a to game object such as light
return_value = ""

function Init()
	return_value = GetVideoScriptStringVariable("video1", "a")
end

function Update()

end
