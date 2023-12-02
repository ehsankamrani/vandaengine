--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguibuttonscriptboolvariable/

--script name is GetGUIButtonScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = GetGUIButtonScriptBoolVariable("gui_pack1_button", "PlayGame", "a")
end

function Update()

end
