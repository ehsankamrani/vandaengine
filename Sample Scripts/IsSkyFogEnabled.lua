--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/isskyfogenabled/

skyFog = false
message = ""

function Init()
	skyFog = IsSkyFogEnabled()

	if skyFog then 
		message = string.format("\nSky fog is ON")
	else
		message = string.format("\nSky fog is OFF")
	end

	PrintConsole(message)
end

function Update()

end


