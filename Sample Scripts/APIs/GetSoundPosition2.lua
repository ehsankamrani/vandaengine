--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundposition/

--Name of script is GetSoundPosition2.lua

posX = 0.0
posY = 0.0
posZ = 0.0

function Init()
	posX, posY, posZ = GetSoundPosition("this")

	message = string.format("\nSound position is > (%.2f, %.2f, %.2f)" , posX, posY, posZ)
	PrintConsole(message)
end

function Update()

end

