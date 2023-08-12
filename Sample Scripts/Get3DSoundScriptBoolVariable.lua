--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/get3dsoundscriptboolvariable/

--script name is Get3DSoundScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = Get3DSoundScriptBoolVariable("sound1", "a")
end

function Update()

end