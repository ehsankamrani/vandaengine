--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/GetEngineCameraAngle/

--Name of script is GetEngineCameraAngle2.lua

angle = 0.0

function Init()
	angle = GetEngineCameraAngle("this")

	message = string.format("\nAngle is > %.2f" , angle )
	PrintConsole(message)
end

function Update()

end
