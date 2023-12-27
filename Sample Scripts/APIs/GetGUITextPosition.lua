--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguitextposition/

x = 0
y = 0
function OnSelectMouseLButtonDown()
		x,y = GetGUITextPosition("gui_test_test", "text1")

		message = string.format("\nGUI text position is > %d, %d" , x,y)
		PrintConsole(message)
end

function OnSelectMouseRButtonDown()

end

function OnSelectMouseEnter()

end
