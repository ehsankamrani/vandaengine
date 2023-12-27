--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/writestringvariabletofile/

sVar = "init"

function Init()
   --Create a folder in Assets/Data/ path
   CreateFolder("Lev1")

   --Create and open file to write data
   OpenFileForWriting("Lev1/level1.bin")
   WriteStringVariableToFile("level1")
   CloseFile("Lev1/level1.bin")

   --Open File to load data
   OpenFileForReading("Lev1/level1.bin")
   sVar = ReadStringVariableFromFile()
   CloseFile("Lev1/level1.bin")
end

