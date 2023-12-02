--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterscriptdoublevariable/

--script name is GetWaterScriptDoubleVariable.lua attached a to game object such as light
return_value = 0.0

function Init()
	return_value = GetWaterScriptDoubleVariable("water1", "a")
end

function Update()

end
