--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterscale/

--Name of script is GetWaterScale2.lua

scaleX = 0.0
scaleZ = 0.0

function Init()
	scaleX, scaleZ = GetWaterScale("this")

	message = string.format("\nWater scale is > (%.2f, %.2f)" , scaleX, scaleZ)
	PrintConsole(message)
end

function Update()

end

