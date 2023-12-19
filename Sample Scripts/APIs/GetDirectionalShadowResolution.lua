--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowresolution/

value = 0

function Init()
	value = GetDirectionalShadowResolution()

	message = string.format("\nDirecional shadow resolution is : %d" ,value)
	PrintConsole(message)
end

function Update()

end
