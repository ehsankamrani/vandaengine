--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeallanimationsofprefabinstances/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseAllAnimationsOfPrefabInstances()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		ResumeAllAnimationsOfPrefabInstances("2_animation_test_plane", "2_animation_test_boy")
	end
end
