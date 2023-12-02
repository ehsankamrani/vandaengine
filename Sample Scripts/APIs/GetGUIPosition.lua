--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getguiposition/

x = 0
y = 0

function Init()
	x,y = GetGUIPosition("gui_SampleGUI17_MainMenu")

	message = string.format("\nGUI position is > %d, %d" , x,y)
	PrintConsole(message)
end

function Update()

end
