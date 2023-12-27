--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getvideoduration/

duration = 0.0

function Init()
	duration = GetVideoDuration("video1")

	message = string.format("\nVideo duration is (%.2f) seconds", duration)
	PrintConsole(message)
end

function Update()

end
