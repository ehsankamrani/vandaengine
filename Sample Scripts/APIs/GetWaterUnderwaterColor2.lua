--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getwaterunderwatercolor/

--Name of script is GetWaterUnderwaterColor2.lua

red = 0.0
green = 0.0
blue = 0.0

function Init()
	red, green, blue = GetWaterUnderwaterColor("this")

	message = string.format("\nUnderwater color of water is > (%.2f, %.2f, %.2f)" , red, green, blue)
	PrintConsole(message)
end

function Update()

end

