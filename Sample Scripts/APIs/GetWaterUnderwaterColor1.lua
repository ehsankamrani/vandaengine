--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterunderwatercolor/

red = 0.0
green = 0.0
blue = 0.0

function Init()
	red, green, blue = GetWaterUnderwaterColor("water1")

	message = string.format("\nUnderwater color of water is > (%.2f, %.2f, %.2f)" , red, green, blue)
	PrintConsole(message)
end

function Update()

end
