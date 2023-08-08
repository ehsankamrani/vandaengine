--Explanations: https://vanda3d.org/addforcetocharactercontroller/

function OnTriggerEnter(otherActorName)
	AddForceToCharacterController(1.0, 10.0, 1.0, 20.0, 20.0)
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end


