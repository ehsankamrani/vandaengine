--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollerwalkspeed/

value = 0.0

function Init()
	value  = GetCharacterControllerWalkSpeed()

	message = string.format("\nCharacter Controller Walk Speed is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

