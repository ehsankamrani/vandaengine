--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicsdefaultstaticfriction/

value = 0.0

function Init()
	value  = GetPhysicsDefaultStaticFriction()

	message = string.format("\nDefault physics static friction is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

