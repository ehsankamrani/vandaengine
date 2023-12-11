--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicsdefaultrestitution/

value = 0.0

function Init()
	value  = GetPhysicsDefaultRestitution()

	message = string.format("\nDefault physics restitution is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

