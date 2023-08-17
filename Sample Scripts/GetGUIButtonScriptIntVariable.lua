--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguibuttonscriptintvariable/

--script name is GetGUIButtonScriptIntVariable.lua attached a to game object such as water
return_value = 0

function Init()
	return_value = GetGUIButtonScriptIntVariable("gui_pack1_button", "PlayGame")
end

function Update()

end
