--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterunderwaterfogdensity/

--Name of script is GetWaterUnderwaterFogDensity2.lua

fog_density = 0.0

function Init()
	fog_density = GetWaterUnderwaterFogDensity("this")

	message = string.format("\nUnderwater fog density of water is > %.2f", fog_density)
	PrintConsole(message)
end

function Update()

end

