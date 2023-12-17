--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollercapsuleheight/

value = 0.0

function Init()
	value  = GetCharacterControllerCapsuleHeight()

	message = string.format("\nCharacter Controller Capsule Height is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

