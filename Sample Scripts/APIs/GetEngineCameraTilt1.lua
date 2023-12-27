--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecameratilt/

tilt = 0.0

function Init()
	tilt = GetEngineCameraTilt("camera1")

	message = string.format("\nTilt is > %.2f" , tilt )
	PrintConsole(message)
end

function Update()

end
