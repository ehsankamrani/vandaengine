--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofallambientsounds/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOfAllAmbientSounds()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		ResumeUpdateEventOfAllAmbientSounds("ambient2", "ambient3")
	end
end
