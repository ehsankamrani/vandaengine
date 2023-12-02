--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/pausemaincharacteranimations/

function OnTriggerEnter(otherActorName)
	--nil means main character controller
	if otherActorName == nil then
		PauseMainCharacterAnimations()
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end
