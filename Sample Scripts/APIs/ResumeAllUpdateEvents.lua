--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeallupdateevents/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseAllUpdateEvents()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		ResumeAllUpdateEvents("water1", "sound1")
	end
end
