--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getscreenheight/

height = 0

function Init()
	height = GetScreenHeight()

	message = string.format("\nScreen height is > %d" , height)
	PrintConsole(message)
end

function Update()

end

