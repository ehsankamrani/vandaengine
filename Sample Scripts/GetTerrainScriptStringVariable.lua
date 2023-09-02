--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getterrainscriptstringvariable/

--script name is GetTerrainScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetTerrainScriptStringVariable("a")
end

function Update()

end
