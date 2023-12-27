--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofprefabinstance/

--Name of script is ResumeUpdateEventOfPrefabInstance2.lua

function Init()
	PauseUpdateEventOfPrefabInstance("this")
	ResumeUpdateEventOfPrefabInstance("this")
end

function Update()
	PrintConsole("\nUpdate")
end
