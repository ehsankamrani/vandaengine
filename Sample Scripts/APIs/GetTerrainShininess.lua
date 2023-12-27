--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getterrainshininess/

shininess = 0.0

function Init()
	shininess  = GetTerrainShininess()

	message = string.format("\nTerrain shininess is > %.2f" ,shininess)
	PrintConsole(message)
end

function Update()

end

