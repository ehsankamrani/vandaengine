--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeanimationofallwaters/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseAnimationOfAllWaters()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		ResumeAnimationOfAllWaters("water2", "water3")
	end
end
