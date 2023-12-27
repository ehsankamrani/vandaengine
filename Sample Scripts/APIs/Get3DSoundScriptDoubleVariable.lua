--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/get3dSoundscriptdoublevariable/

--script name is Get3DSoundScriptDoubleVariable.lua attached a to game object such as water
return_value = 0.0

function Init()
	return_value = Get3DSoundScriptDoubleVariable("sound1", "a")
end

function Update()

end
