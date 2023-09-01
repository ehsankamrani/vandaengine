--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundmaxdistance/

distance = 0

function Init()
	distance = GetSoundMaxDistance("sound1")

	message = string.format("\nSound max distance is > %.2f", distance)
	PrintConsole(message)
end

function Update()

end

