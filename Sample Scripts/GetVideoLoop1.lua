--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoloop/

video_loop = false
message = ""

function Init()
	video_loop = GetVideoLoop("video1")

	if video_loop then 
		message = string.format("\nVideo Loop is ON")
	else
		message = string.format("\nVideo Loop is OFF")
	end

	PrintConsole(message)
end

function Update()

end

