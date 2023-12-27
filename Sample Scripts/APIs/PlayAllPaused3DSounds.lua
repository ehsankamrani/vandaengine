--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallpaused3dsounds/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseAll3DSounds()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		PlayAllPaused3DSounds("river2", "river3")
	end
end
