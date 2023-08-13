--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getambientsoundscriptboolvariable/

--script name is GetAmbientSoundScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = GetAmbientSoundScriptBoolVariable("sound1", "a")
end

function Update()

end
