--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicsdefaultskinwidth/

value = 0.0

function Init()
	value  = GetPhysicsDefaultSkinWidth()

	message = string.format("\nDefault physics skin width is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

