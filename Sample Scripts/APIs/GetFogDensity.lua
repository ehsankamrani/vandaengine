--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getfogdensity/

density = 0.0

function Init()
	density  = GetFogDensity()

	message = string.format("\nFog density is : %.2f" ,density)
	PrintConsole(message)
end

function Update()

end

