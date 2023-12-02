--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getmaincharacterscriptstringvariable/

--script name is GetMainCharacterScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetMainCharacterScriptStringVariable("a")
end

function Update()

end
