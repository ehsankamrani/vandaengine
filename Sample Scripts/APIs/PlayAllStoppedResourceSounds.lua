--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallstoppedresourcesounds/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		LoadResource("Sounds", "fire.ogg")
		LoadResource("Sounds", "river.ogg")
		LoadResource("Sounds", "ambient.ogg")
		PlayAllResourceSoundsLoop()
	end
end

function OnTriggerStay(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		StopAllResourceSounds()
	end
end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		PlayAllStoppedResourceSounds("Sounds_fire.ogg", "Sounds_river.ogg")
	end
end
