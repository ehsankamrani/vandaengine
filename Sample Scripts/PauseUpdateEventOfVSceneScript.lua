--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/pauseupdateeventofvscenescript/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseUpdateEventOfVSceneScript()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
