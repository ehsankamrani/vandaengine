--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterscale/

scaleX = 0.0
scaleZ = 0.0

function Init()
	scaleX, scaleZ = GetWaterScale("water1")

	message = string.format("\nWater scale is > (%.2f, %.2f)" , scaleX, scaleZ)
	PrintConsole(message)
end

function Update()

end
