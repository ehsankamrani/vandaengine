--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightspecular/

red = 0.0
green = 0.0
blue = 0.0

function Init()
		red, green, blue = GetLightSpecular("light1")

		message = string.format("\nLight specular color is > (%.2f, %.2f, %.2f)" , red, green, blue)
		PrintConsole(message)
end

function Update()

end

