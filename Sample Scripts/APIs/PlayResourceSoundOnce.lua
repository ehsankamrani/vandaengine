--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playresourcesoundonce/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		LoadResource("Sounds", "fire.ogg")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PlayResourceSoundOnce("Sounds_fire.ogg")
	end
end
