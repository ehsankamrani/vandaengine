--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallresourcesoundsloop/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		LoadResource("Sounds", "fire.ogg")
		LoadResource("Sounds", "river.ogg")
		LoadResource("Sounds", "ambient.ogg")
	end
end

function OnTriggerStay(otherActorName)
end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		PlayAllResourceSoundsLoop("Sounds_fire.ogg", "Sounds_river.ogg")
	end
end
