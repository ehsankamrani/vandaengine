--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getsoundreferencedistance/

ref_distance = 0.0

function Init()
	ref_distance = GetSoundReferenceDistance("sound1")

	message = string.format("\nSound reference distance is > %.2f", ref_distance)
	PrintConsole(message)
end

function Update()

end
