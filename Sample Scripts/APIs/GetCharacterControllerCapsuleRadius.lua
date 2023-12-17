--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollercapsuleradius/

value = 0.0

function Init()
	value  = GetCharacterControllerCapsuleRadius()

	message = string.format("\nCharacter Controller Capsule Radius is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

