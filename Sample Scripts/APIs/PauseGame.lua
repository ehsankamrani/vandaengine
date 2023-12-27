--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/pausegame/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseGame()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
