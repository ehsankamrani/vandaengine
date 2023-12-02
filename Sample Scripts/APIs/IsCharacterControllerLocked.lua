--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/ischaractercontrollerlocked/

locked = false
message = ""

function Init()
	locked = IsCharacterControllerLocked()

	if locked then 
		message = string.format("\nCharacter controller is locked")
	else
		message = string.format("\nCharacter controller isn't locked")
	end

	PrintConsole(message)
end

function Update()

end


