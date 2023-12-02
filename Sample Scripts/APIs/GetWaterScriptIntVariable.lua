--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterscriptintvariable/

--script name is GetWaterScriptIntVariable.lua attached a to game object such as light
return_value = 0

function Init()
	return_value = GetWaterScriptIntVariable("water1", "a")
end

function Update()

end
