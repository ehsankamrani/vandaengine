--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventof3dsound/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOf3DSound("river1")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		ResumeUpdateEventOf3DSound("river1")
	end

end
