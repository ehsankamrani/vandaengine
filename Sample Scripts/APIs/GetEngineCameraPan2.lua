--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecamerapan/

--Name of script is GetEngineCameraPan2.lua

pan = 0.0

function Init()
	pan = GetEngineCameraPan("this")

	message = string.format("\nPan is > %.2f" , pan )
	PrintConsole(message)
end

function Update()

end
