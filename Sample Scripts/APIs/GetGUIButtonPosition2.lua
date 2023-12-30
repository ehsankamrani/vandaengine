--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguibuttonposition/

--Name of script is GetGUIButtonPosition2.lua

x = 0
y = 0

function OnSelectMouseLButtonDown()
	x,y = GetGUIButtonPosition("this", "PlayGame")

	message = string.format("\nGUI button position is > %d, %d", x, y)
	PrintConsole(message)
end

function OnSelectMouseRButtonDown()

end

function OnSelectMouseEnter()

end
