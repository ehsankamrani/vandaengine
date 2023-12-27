--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallstopped3dsoundsonce/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		StopAll3DSounds()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	if otherActorName == nil then
		PlayAllStopped3DSoundsOnce("river2", "river3")
	end
end
