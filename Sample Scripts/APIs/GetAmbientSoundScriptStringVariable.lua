--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getambientsoundscriptstringvariable/

--script name is GetAmbientSoundScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetAmbientSoundScriptStringVariable("sound1", "a")
end

function Update()

end
