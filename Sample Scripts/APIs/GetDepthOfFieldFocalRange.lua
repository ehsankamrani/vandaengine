--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdepthoffieldfocalrange/

range = 0.0

function Init()
	range  = GetDepthOfFieldFocalRange()

	message = string.format("\nDepth of field focal range is : %.2f" ,range)
	PrintConsole(message)
end

function Update()

end