------------- LOGGING -------------
-- WARNING this causes the game to crash if the log is too long
-- remember to clean it from time to time
on logMsg msg
  set logPath = the moviePath & "patch\\log.txt"
  
  set f = new(xtra "fileio")
  
  -- Create the file if it doesn't exist
  openFile(f, logPath, 0)
  if voidp(fileName(f)) or fileName(f) = EMPTY then
    closeFile(f)
    createFile(f, logPath)
    openFile(f, logPath, 0)
  end if

  -- Move to the end of the file
  setPosition(f, getLength(f))

  -- Write the line
  writeString(f, msg & RETURN)

  closeFile(f)
  set f = 0
end

on clearLog
  set logPath = the moviePath & "patch\\log.txt"

  set f = new(xtra "fileio")

  -- Create an empty file (overwrites existing one)
  createFile(f, logPath)
  openFile(f, logPath, 0)
  writeString(f, "")  -- scrive nulla, file pulito
  closeFile(f)
  set f = 0
end

on getParentPath p
  repeat while (char -1 of p = "\" or char -1 of p = "/")
    delete char -1 of p
  end repeat
  
  repeat with i = the number of chars in p down to 1
    if char i of p = "\" or char i of p = "/" then
      return char 1 to i of p
    end if
  end repeat
  
  return p
end

------------- Movies utilities -------------

on fileExists filePath
  -- Uses Buddy API Xtra (budapi.x32)
  return baFileExists(filePath)
end

on folderExists folderPath
  -- call Buddy API
  if baFolderExists(folderPath) = 1 then
    return TRUE
  else
    return FALSE
  end if
end

on memberExists mName, castNum
  repeat with i = 1 to the number of members of castLib castNum
    if the name of member i of castLib castNum = mName then
      return TRUE
    end if
  end repeat
  return FALSE
end

on castExists cName
  repeat with i = 1 to the number of castLibs
    if string(the name of castLib i) = string(cName) then
      return TRUE
    end if
  end repeat
  return FALSE
end

on listContains lst, val
  repeat with i = 1 to count(lst)
    if getAt(lst, i) = val then
      return TRUE
    end if
  end repeat
  return FALSE
end

on listLoadedCasts
  logMsg("Movie " & the movieName & " casts:")
  repeat with i = 1 to the number of castLibs
    set castName = the name of castLib i
    logMsg("Cast #" & string(i) & ": " & castName)
  end repeat
  logMsg("------------------------")
end

on getCurrentMovieName
  set name = the movieName
  set len = the number of chars in name

  if len > 4 then
    if (char (len - 3) to len of name) = ".dir" or (char (len - 3) to len of name) = ".dxr" or (char (len - 3) to len of name) = ".dcr" then
      set name = char 1 to (len - 4) of name
    end if
  end if

  return name
end