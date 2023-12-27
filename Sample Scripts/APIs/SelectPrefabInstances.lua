--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/selectprefabinstances/

function Init()
	LoadResource("images", "cursor.dds")
	ShowCursorIcon("images_cursor.dds", 5.0)
end

function Update()
	if IsKeyDown("0") then
		SelectPrefabInstances(GetCursorX(), GetCursorY(), 20.0, 20.0)
	end
end
