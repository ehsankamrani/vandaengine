--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/iswatersunreflectionenabled/

waterSunReflection = false
message = ""

function Init()
	waterSunReflection = IsWaterSunReflectionEnabled("water1")

	if waterSunReflection then 
		message = string.format("\nWater sun reflection is enabled")
	else
		message = string.format("\nWater sun reflection is't enabled")
	end

	PrintConsole(message)
end

function Update()

end


