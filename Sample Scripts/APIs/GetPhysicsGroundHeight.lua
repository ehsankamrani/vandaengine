--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getphysicsgroundheight/

value = 0.0

function Init()
	value  = GetPhysicsGroundHeight()

	message = string.format("\nPhysics ground height is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end

