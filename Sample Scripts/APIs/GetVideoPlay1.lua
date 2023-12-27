--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoplay/

video_play = false
message = ""

function Init()
	video_play = GetVideoPlay("video1")

	if video_play then 
		message = string.format("\nVideo is playing")
	else
		message = string.format("\nVideo isn't playing")
	end

	PrintConsole(message)
end

function Update()

end
