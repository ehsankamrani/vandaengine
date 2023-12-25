--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscameranearclipplane/

ncp = 0.0

function Init()
	ncp = GetPhysicsCameraNearClipPlane()

	message = string.format("\nNCP is : %.2f" ,ncp)
	PrintConsole(message)
end

function Update()

end
