--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/deleteresource/

function Init()
	LoadResource("sounds", "mouseHover.ogg")
	LoadResource("images", "pointer.dds")

	DeleteResource("sounds", "mouseHover.ogg")
end

function Update()

end



