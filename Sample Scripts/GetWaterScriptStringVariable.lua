--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterscriptstringvariable/

--script name is GetWaterScriptStringVariable.lua attached a to game object such as light
return_value = ""

function Init()
	return_value = GetWaterScriptStringVariable("water1", "a")
end

function Update()

end
