--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getenginecameraposition/

pos_x = 0.0
pos_y = 0.0
pos_z = 0.0

function Init()
	pos_x, pos_y, pos_z = GetEngineCameraPosition("camera1")

	message = string.format("\nCamera position is > (%.2f, %.2f, %.2f)" , pos_x, pos_y, pos_z)
	PrintConsole(message)
end

function Update()

end
