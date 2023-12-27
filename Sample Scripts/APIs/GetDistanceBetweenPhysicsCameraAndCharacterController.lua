--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdistancebetweenphysicscameraandcharactercontroller/

distance = 0.0

function Init()
	distance  = GetDistanceBetweenPhysicsCameraAndCharacterController()

	message = string.format("\nDistance between physics camera and main character is : %.2f" ,distance)
	PrintConsole(message)
end

function Update()

end

