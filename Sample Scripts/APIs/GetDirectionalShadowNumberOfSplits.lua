--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadownumberofsplits/

value = 0

function Init()
	value = GetDirectionalShadowNumberOfSplits()

	message = string.format("\nDirecional shadow number of splits is : %d" ,value)
	PrintConsole(message)
end

function Update()

end
