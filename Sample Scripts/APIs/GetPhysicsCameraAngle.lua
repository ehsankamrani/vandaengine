--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscameraangle/

angle = 0.0

function Init()
	angle = GetPhysicsCameraAngle()

	message = string.format("\nPhysics camera angle is > %.2f" ,angle)
	PrintConsole(message)
end

function Update()

end
