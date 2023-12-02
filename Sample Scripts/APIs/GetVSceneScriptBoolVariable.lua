--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvscenescriptboolvariable/

--script name is GetVSceneScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = GetVSceneScriptBoolVariable("a")
end

function Update()

end
