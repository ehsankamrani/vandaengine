--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideovolume/

volume = 0.0

function Init()
	volume = GetVideoVolume("video1")

	message = string.format("\nVideo volume is > %.2f", volume)
	PrintConsole(message)
end

function Update()

end
