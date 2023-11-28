--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/stopallresourcesounds/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		LoadResource("Sounds", "fire.ogg")
		LoadResource("Sounds", "river.ogg")
		LoadResource("Sounds", "ambient.ogg")

		PlayResourceSoundLoop("Sounds_fire.ogg")
		PlayResourceSoundLoop("Sounds_river.ogg")
		PlayResourceSoundLoop("Sounds_ambient.ogg")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		StopAllResourceSounds("Sounds_ambient.ogg")
	end
end
