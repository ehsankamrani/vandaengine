--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofallprefabinstances/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOfAllPrefabInstances()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		ResumeUpdateEventOfAllPrefabInstances("1_animation_test_boy", "1_animation_test_plane")
	end
end
