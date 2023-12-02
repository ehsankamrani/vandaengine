--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightshininess/

shininess = 0.0

function Init()
		shininess  = GetLightShininess("light1")

		message = string.format("\nLight shininess is > %.2f" ,shininess)
		PrintConsole(message)
end

function Update()

end

