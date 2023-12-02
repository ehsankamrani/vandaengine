--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getscreenresolution/

resolution = 0

function Init()
	resolution = GetScreenResolution()

	message = string.format("\nScreen resolution is > %d" , resolution)
	PrintConsole(message)
end

function Update()

end

