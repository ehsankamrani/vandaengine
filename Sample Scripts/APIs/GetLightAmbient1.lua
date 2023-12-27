--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightambient/

red = 0.0
green = 0.0
blue = 0.0

function Init()
		red, green, blue = GetLightAmbient("light1")

		message = string.format("\nLight ambient color is > (%.2f, %.2f, %.2f)" , red, green, blue)
		PrintConsole(message)
end

function Update()

end

