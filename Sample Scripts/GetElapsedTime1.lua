--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getelapsedtime/

elapsedTime = 0.0

function Init()

end

function Update()
	elapsedTime = GetElapsedTime()

	message = string.format("\nElapsed time is > %.2f" , elapsedTime)
	PrintConsole(message)
end
