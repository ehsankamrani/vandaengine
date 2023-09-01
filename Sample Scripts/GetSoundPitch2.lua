--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundpitch/

--Name of script is GetSoundPitch2.lua

pitch = 0

function Init()
	pitch = GetSoundPitch("this")

	message = string.format("\nSound pitch is > %.2f", pitch)
	PrintConsole(message)
end

function Update()

end

