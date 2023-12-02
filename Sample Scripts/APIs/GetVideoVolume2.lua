--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideovolume/

--Name of script is GetVideoVolume2.lua

volume = 0.0

function Init()
	volume = GetVideoVolume("this")

	message = string.format("\nVideo volume is > %.2f", volume)
	PrintConsole(message)
end

function Update()

end

