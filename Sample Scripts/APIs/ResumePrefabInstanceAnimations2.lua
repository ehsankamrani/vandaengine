--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeprefabinstanceanimations/

--Name of script is ResumePrefabInstanceAnimations2.lua

pause_animation = true
time = 0.0

function Init()
	PausePrefabInstanceAnimations("this")
end

function Update()
	time = time + GetElapsedTime()
	if pause_animation and time >= 5.0 then
		ResumePrefabInstanceAnimations("this")
		pause_animation = false
	end
end



