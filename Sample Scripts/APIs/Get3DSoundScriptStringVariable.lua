--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/get3dsoundscriptstringvariable/

--script name is Get3DSoundScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = Get3DSoundScriptStringVariable("sound1", "a")
end

function Update()

end
