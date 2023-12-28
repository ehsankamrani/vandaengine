--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguiimageposition/

--Name of script is GetGUIImagePosition2.lua

x = 0
y = 0
function OnSelectMouseLButtonDown()
	x,y = GetGUIImagePosition("this", "image1")

	message = string.format("\nGUI image position is > %d, %d" , x,y)
	PrintConsole(message)
end

function OnSelectMouseRButtonDown()

end

function OnSelectMouseEnter()

end
