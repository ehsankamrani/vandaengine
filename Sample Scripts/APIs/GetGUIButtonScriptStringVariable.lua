--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguibuttonscriptstringvariable/

--script name is GetGUIButtonScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetGUIButtonScriptStringVariable("gui_pack1_button", "PlayGame", "a")
end

function Update()

end
