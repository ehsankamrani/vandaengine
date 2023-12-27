--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/openfileforreading/

bVar = false
fVar = 0.0
iVar = 0
sVar = "init"

function Init()
   --Create a folder in Assets/Data/ path
   CreateFolder("Lev1")

   --Create and open file to write data
   OpenFileForWriting("Lev1/level1.bin")
   WriteBoolVariableToFile(true)
   WriteFloatVariableToFile(2.0)
   WriteIntVariableToFile(3)
   WriteStringVariableToFile("level1")
   CloseFile("Lev1/level1.bin")

   --Open File to load data
   OpenFileForReading("Lev1/level1.bin")
   bVar = ReadBoolVariableFromFile()
   fVar = ReadFloatVariableFromFile()
   iVar = ReadIntVariableFromFile()
   sVar = ReadStringVariableFromFile()
   CloseFile("Lev1/level1.bin")
end

