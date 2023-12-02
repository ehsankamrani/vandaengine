--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoscriptboolvariable/

--script name is GetVideoScriptBoolVariable.lua attached a to game object such as light
return_value = false

function Init()
	return_value = GetVideoScriptBoolVariable("video1", "a")
end

function Update()

end
