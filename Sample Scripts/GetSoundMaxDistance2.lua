--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundmaxdistance/

--Name of script is GetSoundMaxDistance2.lua

distance = 0

function Init()
	distance = GetSoundMaxDistance("this")

	message = string.format("\nSound max distance is > %.2f", distance)
	PrintConsole(message)
end

function Update()

end

