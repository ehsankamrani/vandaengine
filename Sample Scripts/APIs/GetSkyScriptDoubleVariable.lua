--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getskyscriptdoublevariable/

--script name is GetSkyScriptDoubleVariable.lua attached a to game object such as water
return_value = 0.0

function Init()
	return_value = GetSkyScriptDoubleVariable("a")
end

function Update()

end
