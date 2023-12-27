--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showgui/

function OnTriggerEnter(otherActorName)
	HideGUI("gui_SampleGUI17_MainMenu")
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	ShowGUI("gui_SampleGUI17_MainMenu")
end
