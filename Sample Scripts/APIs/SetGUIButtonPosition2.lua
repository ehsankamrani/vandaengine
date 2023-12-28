--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setguibuttonposition/

--Name of script is SetGUIButtonPosition2.lua

function OnSelectMouseLButtonDown()
	SetGUIButtonPosition("this", "PlayGame", GetScreenWidth() / 2, GetScreenHeight() / 2)
end

function OnSelectMouseRButtonDown()

end

function OnSelectMouseEnter()

end
