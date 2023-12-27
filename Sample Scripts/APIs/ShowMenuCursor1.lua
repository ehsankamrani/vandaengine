--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showmenucursor/

function OnTriggerEnter(otherActorName)
	ShowMenuCursor(4)
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	HideMenuCursor()
end
