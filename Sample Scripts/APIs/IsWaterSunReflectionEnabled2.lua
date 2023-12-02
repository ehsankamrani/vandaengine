--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/iswatersunreflectionenabled/

--Name of script is IsWaterSunReflectionEnabled2.lua

waterSunReflection = false
message = ""

function Init()
	waterSunReflection = IsWaterSunReflectionEnabled("this")

	if waterSunReflection then 
		message = string.format("\nWater sun reflection is enabled")
	else
		message = string.format("\nWater sun reflection is't enabled")
	end

	PrintConsole(message)
end

function Update()

end


