--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoplay/

--Name of script is GetVideoPlay2.lua

video_play = false
message = ""

function Init()
	video_play = GetVideoPlay("this")

	if video_play then 
		message = string.format("\nVideo is playing")
	else
		message = string.format("\nVideo isn't playing")
	end

	PrintConsole(message)
end

function Update()

end

