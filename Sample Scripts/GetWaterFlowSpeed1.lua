--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterflowspeed/

speed = 0.0

function Init()
	speed = GetWaterFlowSpeed("water1")

	message = string.format("\nWater flow speed is > %.2f", speed)
	PrintConsole(message)
end

function Update()

end
