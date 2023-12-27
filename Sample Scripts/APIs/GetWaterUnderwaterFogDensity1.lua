--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterunderwaterfogdensity/

fog_density = 0.0

function Init()
	fog_density = GetWaterUnderwaterFogDensity("water1")

	message = string.format("\nUnderwater fog density of water is > %.2f", fog_density)
	PrintConsole(message)
end

function Update()

end
