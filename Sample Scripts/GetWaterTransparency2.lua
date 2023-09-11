--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwatertransparency/

--Name of script is GetWaterTransparency2.lua

transparency = 0.0

function Init()
	transparency = GetWaterTransparency("this")

	message = string.format("\nWater transparency is > %.2f", transparency)
	PrintConsole(message)
end

function Update()

end

