--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicsactorgroup/

function OnTriggerEnter(otherActorName)
	if GetPhysicsActorGroup(otherActorName) == "KINEMATIC" then PrintConsole("\nKinematic Actor")
	elseif GetPhysicsActorGroup(otherActorName) == "DYNAMIC" then PrintConsole("\nDynamic Actor")
	end
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end


