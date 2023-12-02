--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecameratilt/

--Name of script is GetEngineCameraTilt2.lua

tilt = 0.0

function Init()
	tilt = GetEngineCameraTilt("this")

	message = string.format("\nTilt is > %.2f" , tilt )
	PrintConsole(message)
end

function Update()

end
