--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundloop/

sound_loop = 0
message = ""

function Init()
	sound_loop = GetSoundLoop("sound1")

	if sound_loop then 
		message = string.format("\nSound Loop is ON")
	else
		message = string.format("\nSound Loop is OFF")
	end

	PrintConsole(message)
end

function Update()

end

