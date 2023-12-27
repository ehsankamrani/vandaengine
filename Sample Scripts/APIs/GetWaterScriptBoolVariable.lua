--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterscriptboolvariable/

--script name is GetWaterScriptBoolVariable.lua attached a to game object such as light
return_value = false

function Init()
	return_value = GetWaterScriptBoolVariable("water1", "a")
end

function Update()

end
