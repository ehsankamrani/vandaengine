--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecamerafarclipplane/

fcp = 0.0

function Init()
	fcp = GetEngineCameraFarClipPlane("camera1")

	message = string.format("\nFar Clip Plane is > %.2f" , fcp)
	PrintConsole(message)
end

function Update()

end
