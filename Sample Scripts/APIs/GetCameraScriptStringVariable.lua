--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcamerascriptstringvariable/

--script name is GetCameraScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetCameraScriptStringVariable("camera1", "a")
end

function Update()

end
