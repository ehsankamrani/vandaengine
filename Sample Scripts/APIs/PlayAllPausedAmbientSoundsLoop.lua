--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallpausedambientsoundsloop/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseAllAmbientSounds()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		PlayAllPausedAmbientSoundsLoop("ambient2", "ambient3")
	end
end
