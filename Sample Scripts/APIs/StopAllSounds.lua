--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/stopallsounds/

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
		StopAllSounds("ambient2", "river2", "Sounds_ambient.ogg")
	end
end
