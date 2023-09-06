--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoscriptintvariable/

--script name is GetVideoScriptIntVariable.lua attached a to game object such as light
return_value = 0

function Init()
	return_value = GetVideoScriptIntVariable("video1", "a")
end

function Update()

end
