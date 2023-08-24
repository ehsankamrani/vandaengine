--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscameramintilt/

minTilt = 0.0

function Init()
	minTilt = GetPhysicsCameraMinTilt()

	message = string.format("\nPhysics camera min tilt is > %.2f" ,minTilt)
	PrintConsole(message)
end

function Update()

end
