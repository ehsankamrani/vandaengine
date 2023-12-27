--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showguitext/

function OnTriggerEnter(otherActorName)
	HideGUIText("gui_SampleGUI17_MainMenuAbout", "text1")
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	ShowGUIText("gui_SampleGUI17_MainMenuAbout", "text1")
end
