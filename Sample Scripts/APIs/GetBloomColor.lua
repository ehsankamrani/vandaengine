--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getbloomcolor/

red = 0.0
green = 0.0
blue = 0.0

function Init()
	red, green, blue = GetBloomColor()

	message = string.format("\nBloom color is : (%.2f, %.2f, %.2f)" , red, green, blue)
	PrintConsole(message)
end

function Update()

end

