--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundreferencedistance/

--Name of script is GetSoundReferenceDistance2.lua

ref_distance = 0.0

function Init()
	ref_distance = GetSoundReferenceDistance("this")

	message = string.format("\nSound reference distance is > %.2f", ref_distance)
	PrintConsole(message)
end

function Update()

end

