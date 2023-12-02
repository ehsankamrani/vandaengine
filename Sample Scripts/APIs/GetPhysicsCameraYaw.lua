--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscamerayaw/

yaw = 0.0

function Init()

end

function Update()
	yaw = GetPhysicsCameraYaw()

	message = string.format("\nPhysics camera yaw is > %.2f" ,yaw)
	PrintConsole(message)
end
