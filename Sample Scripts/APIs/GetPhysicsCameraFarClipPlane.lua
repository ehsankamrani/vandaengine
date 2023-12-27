--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscamerafarclipplane/

fcp = 0.0

function Init()
	fcp = GetPhysicsCameraFarClipPlane()

	message = string.format("\nFCP is : %.2f" ,fcp)
	PrintConsole(message)
end

function Update()

end
