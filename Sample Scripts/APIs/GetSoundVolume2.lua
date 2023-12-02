--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundvolume/

--Name of script is GetSoundVolume2.lua

volume = 0.0

function Init()
	volume = GetSoundVolume("this")

	message = string.format("\nSound volume is > %.2f", volume)
	PrintConsole(message)
end

function Update()

end

