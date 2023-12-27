--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/pauseupdateeventofallwaters/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOfAllWaters("water2", "water3")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
