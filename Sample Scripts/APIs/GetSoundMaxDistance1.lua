--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundmaxdistance/

max_distance = 0.0

function Init()
	max_distance = GetSoundMaxDistance("sound1")

	message = string.format("\nSound max distance is > %.2f", max_distance)
	PrintConsole(message)
end

function Update()

end

