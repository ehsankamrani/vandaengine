--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowlight/

value = ""

function Init()
	value = GetDirectionalShadowLight()

	message = string.format("\nDirectional shadow light name is : %s" ,value)
	PrintConsole(message)
end

function Update()

end
