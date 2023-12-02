--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showguibutton/

function OnTriggerEnter(otherActorName)
	HideGUIButton("gui_SampleGUI17_MainMenu", "PlayGame")
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	ShowGUIButton("gui_SampleGUI17_MainMenu", "PlayGame")
end
