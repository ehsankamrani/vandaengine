--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdepthoffieldfocaldistance/

distance = 0.0

function Init()
	distance  = GetDepthOfFieldFocalDistance()

	message = string.format("\nDepth of field focal distance is : %.2f" ,distance)
	PrintConsole(message)
end

function Update()

end

