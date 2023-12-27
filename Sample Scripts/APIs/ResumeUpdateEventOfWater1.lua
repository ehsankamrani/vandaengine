--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofwater/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOfWater("water1")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		ResumeUpdateEventOfWater("water1")
	end

end
