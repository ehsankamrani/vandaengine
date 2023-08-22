--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getmenucursorsize/

value = 0

function Init()
	value = GetMenuCursorSize()

	message = string.format("\nMenu cursor size is > %d" ,value )
	PrintConsole(message)
end

function Update()

end
