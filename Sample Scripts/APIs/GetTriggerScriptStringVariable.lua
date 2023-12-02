--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/gettriggerscriptstringvariable/

--script name is GetTriggerScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetTriggerScriptStringVariable("trigger1", "a")
end

function Update()

end
