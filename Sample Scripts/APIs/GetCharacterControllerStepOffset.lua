--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollerstepoffset/

value = 0.0

function Init()
	value  = GetCharacterControllerStepOffset()

	message = string.format("\nCharacter Controller Step Offset is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

