--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getelapsedtime/

elaspedTime = 0.0

function Init()

end

function Update()
	elaspedTime = GetElapsedTime()

	message = string.format("\nElasped time is > %.2f" , elaspedTime )
	PrintConsole(message)
end
