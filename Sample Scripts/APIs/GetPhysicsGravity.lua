--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicsgravity/

x = 0.0
y = 0.0
z = 0.0

function Init()
	x, y, z = GetPhysicsGravity()

	message = string.format("\nPhysics gravity is : (%.2f, %.2f, %.2f)" , x, y, z)
	PrintConsole(message)
end

function Update()

end

