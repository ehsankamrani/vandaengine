--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/playall3dsoundsloop/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PlayAll3DSoundsLoop("sound3D_2", "sound3D_3")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
