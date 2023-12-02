--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterposition/

--Name of script is GetWaterPosition2.lua

posX = 0.0
posY = 0.0
posZ = 0.0

function Init()
	posX, posY, posZ = GetWaterPosition("this")

	message = string.format("\nWater position is > (%.2f, %.2f, %.2f)" , posX, posY, posZ)
	PrintConsole(message)
end

function Update()

end

