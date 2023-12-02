--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundmaxdistance/

--Name of script is GetSoundMaxDistance2.lua

max_distance = 0.0

function Init()
	max_distance = GetSoundMaxDistance("this")

	message = string.format("\nSound max distance is > %.2f", max_distance)
	PrintConsole(message)
end

function Update()

end

