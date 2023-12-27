--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterflowspeed/

--Name of script is GetWaterFlowSpeed2.lua

speed = 0.0

function Init()
	speed = GetWaterFlowSpeed("this")

	message = string.format("\nWater flow speed is > %.2f", speed)
	PrintConsole(message)
end

function Update()

end

