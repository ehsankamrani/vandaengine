--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofwater/

--Name of script is ResumeUpdateEventOfWater2.lua

function Init()
	PauseUpdateEventOfWater("this")

	ResumeUpdateEventOfWater("this")
end

function Update()
	PrintConsole("\nUpdate")
end
