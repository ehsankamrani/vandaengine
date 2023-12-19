--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowweightofsplits/

value = 0.0

function Init()
	value = GetDirectionalShadowWeightOfSplits()

	message = string.format("\nDirecional shadow weight of splits is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end
