--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundpitch/

pitch = 0

function Init()
	pitch = GetSoundPitch("sound1")

	message = string.format("\nSound pitch is > %.2f", pitch)
	PrintConsole(message)
end

function Update()

end

