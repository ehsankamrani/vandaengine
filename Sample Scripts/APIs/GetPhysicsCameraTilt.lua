--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscameratilt/

tilt = 0.0

function Init()

end

function Update()
	tilt = GetPhysicsCameraTilt()

	message = string.format("\nPhysics camera tilt is > %.2f" ,tilt)
	PrintConsole(message)
end
