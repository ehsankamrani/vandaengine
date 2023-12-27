--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/stopvideo/

--You can attach this script to a video object named "video1"

timer = 0.0
stop = false

function Init()
	PlayVideo("video1")
end

function Update()
	timer = timer + GetElapsedTime()
	if timer >= (GetVideoDuration("video1") / 5.0) and not stop then
		StopVideo("video1")
		stop = true
	end
end
