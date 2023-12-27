--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeprefabinstanceanimations/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PausePrefabInstanceAnimations("1_animation_test_plane")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		ResumePrefabInstanceAnimations("1_animation_test_plane")
	end
end
