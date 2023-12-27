--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/pauseresourcesound/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		LoadResource("Sounds", "fire.ogg")
		PlayResourceSoundLoop("Sounds_fire.ogg")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseResourceSound("Sounds_fire.ogg")
	end
end
