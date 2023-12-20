--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowintensity/

value = 0.0

function Init()
	value = GetDirectionalShadowIntensity()

	message = string.format("\nDirectional shadow intensity is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end
