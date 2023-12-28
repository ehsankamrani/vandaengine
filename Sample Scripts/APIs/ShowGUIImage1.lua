--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showguiimage/

function OnTriggerEnter(otherActorName)
	HideGUIImage("gui_SampleGUI17_MainMenuAbout", "backgroundImg")
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	ShowGUIImage("gui_SampleGUI17_MainMenuAbout", "backgroundImg")
end
