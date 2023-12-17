--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollerjumppower/

value = 0.0

function Init()
	value  = GetCharacterControllerJumpPower()

	message = string.format("\nCharacter Controller Jump Power is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

