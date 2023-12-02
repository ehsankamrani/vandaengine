--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguibuttonposition/

x = 0
y = 0
function OnSelectMouseLButtonDown()
	x,y = GetGUIButtonPosition("gui_test_test", "PlayGame")

	message = string.format("\nGUI button position is > %d, %d", x, y)
	PrintConsole(message)
end

function OnSelectMouseRButtonDown()

end

function OnSelectMouseEnter()

end
