--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getselectiondistance/

selection_distance = 0.0

function Init()
	SetSelectionDistance(5.5)

	selection_distance = GetSelectionDistance()

	message = string.format("\nSelection distance is > %.2f" , selection_distance)
	PrintConsole(message)
end

function Update()

end
