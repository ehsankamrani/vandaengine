--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterrotation/

--Name of script is GetWaterRotation2.lua

rotation = 0.0

function Init()
	rotation = GetWaterRotation("this")

	message = string.format("\nWater rotation is > %.2f", rotation)
	PrintConsole(message)
end

function Update()

end

