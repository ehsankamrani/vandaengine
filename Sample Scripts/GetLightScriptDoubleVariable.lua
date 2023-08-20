--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightscriptdoublevariable/

--script name is GetLightScriptDoubleVariable.lua attached a to game object such as water
return_value = 0.0

function Init()
	return_value = GetLightScriptDoubleVariable("light1", "a")
end

function Update()

end
