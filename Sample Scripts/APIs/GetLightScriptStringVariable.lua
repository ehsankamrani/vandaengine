--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightscriptstringvariable/

--script name is GetLightScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetLightScriptStringVariable("light1", "a")
end

function Update()

end
