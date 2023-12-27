--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventoflight/

--Name of script is ResumeUpdateEventOfLight2.lua

function Init()
	PauseUpdateEventOfLight("this")

	ResumeUpdateEventOfLight("this")
end

function Update()
	PrintConsole("\nUpdate")
end
