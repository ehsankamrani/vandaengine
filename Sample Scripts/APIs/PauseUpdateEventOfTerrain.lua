--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/pauseupdateeventofterrain/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOfTerrain()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
