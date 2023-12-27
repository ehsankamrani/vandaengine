--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getterrainscriptdoublevariable/

--script name is GetTerrainScriptDoubleVariable.lua attached a to game object such as water
return_value = 0.0

function Init()
	return_value = GetTerrainScriptDoubleVariable("a")
end

function Update()

end
