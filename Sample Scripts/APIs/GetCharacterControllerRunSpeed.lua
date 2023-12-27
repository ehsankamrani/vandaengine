--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getcharactercontrollerrunspeed/

value = 0.0

function Init()
	value  = GetCharacterControllerRunSpeed()

	message = string.format("\nCharacter Controller Run Speed is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

