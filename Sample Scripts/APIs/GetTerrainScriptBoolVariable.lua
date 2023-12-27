--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getterrainscriptboolvariable/

--script name is GetTerrainScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = GetTerrainScriptBoolVariable("a")
end

function Update()

end
