--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setselectiondistance/

function Init()
	LoadResource("images", "cursor.dds")
	ShowCursorIcon("images_cursor.dds", 5.0)
	SetSelectionDistance(5.5)
end

function Update()
	if IsKeyDown("0") then
		SelectPrefabInstances(GetCursorX(), GetCursorY(), 20.0, 20.0)
	end
end
