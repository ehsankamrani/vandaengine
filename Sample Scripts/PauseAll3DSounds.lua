--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/lockcharactercontroller/

function OnTriggerEnter(otherActorName)
	--if character controller enters trigger, pause all 3D sounds except a 3D sound named "sound3D_2"
	if otherActorName == nil then
		PauseAll3DSounds("sound3D_2")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
