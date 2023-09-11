--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwateruv/

UV = 0.0

function Init()
	UV = GetWaterUV("water1")

	message = string.format("\nWater UV is > %.2f", UV)
	PrintConsole(message)
end

function Update()

end
