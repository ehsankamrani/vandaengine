--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/get3dsoundscriptintvariable/

--script name is Get3DSoundScriptIntVariable.lua attached a to game object such as water
return_value = 0

function Init()
	return_value = Get3DSoundScriptIntVariable("sound1", "a")
end

function Update()

end
