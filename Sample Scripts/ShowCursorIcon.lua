--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showcursoricon/

timer = 0.0
hidden = false

function Init()
	LoadResource("Images", "Cursor.dds")
	ShowCursorIcon("Images_Cursor.dds", 5.0)
end

function Update()
	if timer < 5.0 then timer = timer + GetElapsedTime() end

	if timer >= 5.0 and not hidden then
		HideCursorIcon("Images_Cursor.dds")
		hidden = true
	end
end
