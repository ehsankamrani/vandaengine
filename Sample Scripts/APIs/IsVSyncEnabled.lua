--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/isvsyncenabled/

VSync = false
message = ""

function Init()
	VSync = IsVSyncEnabled()

	if VSync then 
		message = string.format("\nVSync is ON")
	else
		message = string.format("\nVSync is OFF")
	end

	PrintConsole(message)
end

function Update()

end


