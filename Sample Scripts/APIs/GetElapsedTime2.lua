--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getelapsedtime/

elapsedSeconds = 0.0

function Init()

end

function Update()
	elapsedSeconds = elapsedSeconds + GetElapsedTime()

	message = string.format("\nElapsed seconds is > %.2f" , elapsedSeconds )
	PrintConsole(message)
end
