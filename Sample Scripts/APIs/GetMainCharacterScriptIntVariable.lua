--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getmaincharacterscriptintvariable/

--script name is GetMainCharacterScriptIntVariable.lua attached a to game object such as water
return_value = 0

function Init()
	return_value = GetMainCharacterScriptIntVariable("a")
end

function Update()

end
