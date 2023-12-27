--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightscriptintvariable/

--script name is GetLightScriptIntVariable.lua attached a to game object such as water
return_value = 0

function Init()
	return_value = GetLightScriptIntVariable("light1", "a")
end

function Update()

end
