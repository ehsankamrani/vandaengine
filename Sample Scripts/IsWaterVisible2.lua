--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/iswatervisible/

--Name of script is IsWaterVisible2.lua

water_visible = false
message = ""

function Init()
	water_visible = IsWaterVisible("this")

	if water_visible then 
		message = string.format("\nWater is visible")
	else
		message = string.format("\nWater is invisible")
	end

	PrintConsole(message)
end

function Update()

end


