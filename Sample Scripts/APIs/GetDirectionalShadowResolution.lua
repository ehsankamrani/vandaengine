--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowresolution/

value = 0

function Init()
	value = GetDirectionalShadowResolution()

	message = string.format("\nDirectional shadow resolution is : %d" ,value)
	PrintConsole(message)
end

function Update()

end
