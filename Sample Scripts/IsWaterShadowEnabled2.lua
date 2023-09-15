--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/iswatershadowenabled/

--Name of script is IsWaterShadowEnabled2.lua

waterShadow = false
message = ""

function Init()
	waterShadow = IsWaterShadowEnabled("this")

	if waterShadow then 
		message = string.format("\nWater shadow is enabled")
	else
		message = string.format("\nWater shadow is't enabled")
	end

	PrintConsole(message)
end

function Update()

end


