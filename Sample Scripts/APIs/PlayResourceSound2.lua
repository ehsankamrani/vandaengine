--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playresourcesound/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		LoadResource("Sounds", "fire.ogg")
		PlayAllResourceSoundsOnce()
		StopAllResourceSounds()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PlayResourceSound("Sounds_fire.ogg")
	end
end
