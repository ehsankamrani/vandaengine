--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecameranearclipplane/

--Name of script is GetEngineCameraNearClipPlane2.lua
ncp = 0.0

function Init()
	ncp = GetEngineCameraNearClipPlane("this")

	message = string.format("\nNear Clip Plane is > %.2f" , ncp)
	PrintConsole(message)
end

function Update()

end
