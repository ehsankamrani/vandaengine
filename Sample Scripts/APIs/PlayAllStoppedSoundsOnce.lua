--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallstoppedsoundsonce/

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
		StopAllSounds()
	end
end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		PlayAllStoppedSoundsOnce("ambient2", "river_3D2", "Sounds_fire.ogg", "Sounds_river.ogg")
	end
end
