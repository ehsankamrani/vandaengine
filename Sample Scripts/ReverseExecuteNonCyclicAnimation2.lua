--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/reverseexecutenoncyclicanimation/

--name of script is ReverseExecuteNonCyclicAnimation2.lua

animation = true
animation_time = 0.0
time = 0.0

function Init()
	ExecuteNonCyclicAnimation("this", "defaultClip", 0.5, 0.7, 1.0, false)

	animation_time = GetAnimationClipDurationOfPrefabInstance("this", "defaultClip")
end

function Update()
	time = time + GetElapsedTime()

	if animation == true and time > animation_time / 2.0 then 
		ReverseExecuteNonCyclicAnimation("this", "defaultClip")
		animation = false
	end
end




