--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/isgeneralwaterreflectionenabled/

reflection = false
message = ""

function Init()
	reflection = IsGeneralWaterReflectionEnabled()

	if reflection then 
		message = string.format("\nGeneral water reflection is ON")
	else
		message = string.format("\nGeneral water reflection is OFF")
	end

	PrintConsole(message)
end

function Update()

end


