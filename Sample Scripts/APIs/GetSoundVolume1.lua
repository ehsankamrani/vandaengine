--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundvolume/

volume = 0.0

function Init()
	volume = GetSoundVolume("sound1")

	message = string.format("\nSound volume is > %.2f", volume)
	PrintConsole(message)
end

function Update()

end
