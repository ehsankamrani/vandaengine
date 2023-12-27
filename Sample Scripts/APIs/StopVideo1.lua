--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/stopvideo/

--Name of script is StopVideo1.lua
--You can attach this script to a video object

timer = 0.0
stop = false

function Init()
	PlayVideo("this")
end

function Update()
	timer = timer + GetElapsedTime()
	if timer >= (GetVideoDuration("this") / 5.0) and not stop then
		StopVideo("this")
		stop = true
	end
end
