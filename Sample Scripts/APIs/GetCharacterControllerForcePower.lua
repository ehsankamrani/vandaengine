--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollerforcepower/

value = 0.0

function Init()
	value  = GetCharacterControllerForcePower()

	message = string.format("\nCharacter Controller Force Power is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

