--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecamerafarclipplane/

--Name of script is GetEngineCameraFarClipPlane2.lua
fcp = 0.0

function Init()
	fcp = GetEngineCameraFarClipPlane("this")

	message = string.format("\nFar Clip Plane is > %.2f" , fcp)
	PrintConsole(message)
end

function Update()

end
