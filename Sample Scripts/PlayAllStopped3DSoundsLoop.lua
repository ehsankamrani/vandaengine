--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playallstopped3dsoundsloop/

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
		PlayAllStopped3DSoundsLoop("river2", "river3")
	end
end
