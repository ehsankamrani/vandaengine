--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscameramaxtilt/

maxTilt = 0.0

function Init()
	maxTilt = GetPhysicsCameraMaxTilt()

	message = string.format("\nPhysics camera max tilt is > %.2f" ,maxTilt)
	PrintConsole(message)
end

function Update()

end
