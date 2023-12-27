--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getbloomintensity/

intensity = 0.0

function Init()
	intensity  = GetBloomIntensity()

	message = string.format("\nBloom intensity is : %.2f" ,intensity)
	PrintConsole(message)
end

function Update()

end

