--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcamerascriptboolvariable/

--script name is GetCameraScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = GetCameraScriptBoolVariable("camera1", "a")
end

function Update()

end
