--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicscollisionflags/

flag = false
message = ""

function Init()
	flag  = GetPhysicsCollisionFlags("DYNAMIC", "KINEMATIC")

	if flag == true then
		message = string.format("\nCollision detection between dynamic and kinematic actors is 'true'")
	else
		message = string.format("\nCollision detection between dynamic and kinematic actors is 'false'")
	end

	PrintConsole(message)
end

function Update()

end

