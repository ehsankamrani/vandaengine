--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowalgorithm/

value = ""

function Init()
	value = GetDirectionalShadowAlgorithm()

	message = string.format("\nDirectional shadow algorithm is : %s" ,value)
	PrintConsole(message)
end

function Update()

end
