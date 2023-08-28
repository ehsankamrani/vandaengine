--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getscreenwidth/

width = 0

function Init()
	width = GetScreenWidth()

	message = string.format("\nScreen width is > %d" , width)
	PrintConsole(message)
end

function Update()

end

