--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterrotation/

rotation = 0.0

function Init()
	rotation = GetWaterRotation("water1")

	message = string.format("\nWater rotation is > %.2f", rotation)
	PrintConsole(message)
end

function Update()

end
