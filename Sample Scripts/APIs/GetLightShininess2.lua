--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getlightshininess/

--Script name is GetLightShininess2.lua

shininess = 0.0

function Init()
			shininess  = GetLightShininess("this")

			message = string.format("\nLight shininess is > %.2f" ,shininess)
			PrintConsole(message)
end

function Update()

end

