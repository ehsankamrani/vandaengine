--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundplay/

--Name of script is GetSoundPlay2.lua

sound_play = false
message = ""

function Init()
	sound_play = GetSoundPlay("this")

	if sound_play then 
		message = string.format("\nSound is playing")
	else
		message = string.format("\nSound isn't playing")
	end

	PrintConsole(message)
end

function Update()

end

