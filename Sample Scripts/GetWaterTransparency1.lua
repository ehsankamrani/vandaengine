--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwatertransparency/

transparency = 0.0

function Init()
	transparency = GetWaterTransparency("water1")

	message = string.format("\nWater transparency is > %.2f", transparency)
	PrintConsole(message)
end

function Update()

end
