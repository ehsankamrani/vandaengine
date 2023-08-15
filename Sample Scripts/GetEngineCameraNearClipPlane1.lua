--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecameranearclipplane/

ncp = 0.0

function Init()
	ncp = GetEngineCameraNearClipPlane("camera1")

	message = string.format("\nNear Clip Plane is > %.2f" , ncp)
	PrintConsole(message)
end

function Update()

end
