--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecamerapan/

pan = 0.0

function Init()
	pan = GetEngineCameraPan("camera1")

	message = string.format("\nPan is > %.2f" , pan )
	PrintConsole(message)
end

function Update()

end
