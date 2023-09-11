--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwateruv/

--Name of script is GetWaterUV2.lua

UV = 0.0

function Init()
	UV = GetWaterUV("this")

	message = string.format("\nWater UV is > %.2f", UV)
	PrintConsole(message)
end

function Update()

end

