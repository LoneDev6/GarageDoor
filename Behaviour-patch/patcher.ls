global gPatchingStarted

on startMovie
  set gPatchingStarted = FALSE
  clearLog()
  logMsg("=== Injector started at " & the date && the time & " ===")
  
  -- Delay di sicurezza per permettere al movie di caricarsi
  sendSprite(0, #delayedPatching)
end

on delayedPatching
  repeat with i = 1 to 5
    updateStage
  end repeat
  
  listLoadedCasts()
  applyAllPatches(the moviePath & "patch\\")
  logMsg("--- All patching complete ---")
end


on applyAllPatches basePath
  set currentMovie = getCurrentMovieName()
  
  repeat with i = 1 to the number of castLibs
    set castName = the name of castLib i
    if castName = EMPTY then next repeat
    
    set castFile = the fileName of castLib i
    
    if i = 1 or castFile = EMPTY then
      -- INTERNAL CAST
      logMsg("Patching internal cast: " & castName)
      patchInternalCast currentMovie, i, castName, basePath
    else
      -- EXTERNAL CAST
      logMsg("Patching external cast: " & castName)
      patchExternalCast castFile, castName, basePath
    end if
    
    updateStage
  end repeat
end


-----------------------------------------------
-- PATCH EXTERNAL CAST
-----------------------------------------------
on patchExternalCast castFile, castName, basePath
  set patchedCount = 0
  global gFileIO
  if voidp(gFileIO) then
    set gFileIO = new(xtra "FileIO")
  end if
  
  -- Folder name = name of cast file (without extension)
  set castFolder = basePath & removeExtension(getFileNameFromPath(castFile))
  
  if not folderExists(castFolder) then
    logMsg("No folder found for external cast: " & castName)
    exit
  end if
  
  repeat with i = 1 to 300
    set bmpPath = castFolder & "\\" & string(i) & ".bmp"
    set txtPath = castFolder & "\\" & string(i) & ".txt"
    
    if fileExists(bmpPath) = 1 then
      replaceBitmap(member(i) of castLib castName, bmpPath)
      set patchedCount = patchedCount + 1
    else if fileExists(txtPath) = 1 then
      replaceField(member(i) of castLib castName, txtPath)
      set patchedCount = patchedCount + 1
    end if
  end repeat
  
  if patchedCount = 0 then
    logMsg("No patches found for external cast: " & castName)
  else
    logMsg("Patched " & string(patchedCount) & " members for external cast: " & castName)
  end if
end


-----------------------------------------------
-- PATCH INTERNAL CAST
-----------------------------------------------
on patchInternalCast movieName, castIndex, castName, basePath
  set patchedCount = 0
  global gFileIO
  if voidp(gFileIO) then
    set gFileIO = new(xtra "FileIO")
  end if
  
  set castFolder = basePath & movieName & "\\"
  
  repeat with i = 1 to 300
    set bmpPath = castFolder & string(castIndex) & "_" & string(i) & ".bmp"
    set txtPath = castFolder & string(castIndex) & "_" & string(i) & ".txt"
    
    if fileExists(bmpPath) = 1 then
      replaceBitmap(member(i) of castLib castName, bmpPath)
      set patchedCount = patchedCount + 1
    else if fileExists(txtPath) = 1 then
      replaceField(member(i) of castLib castName, txtPath)
      set patchedCount = patchedCount + 1
    end if
  end repeat
  
  if patchedCount = 0 then
    logMsg("No patches found for internal cast: " & castName)
  else
    logMsg("Patched " & string(patchedCount) & " members for internal cast: " & castName)
  end if
end

-----------------------------------------------
-- REPLACEMENT LOGIC
-----------------------------------------------
on replaceBitmap bitmapMember, bitmapFileName
  if the type of bitmapMember <> #bitmap then exit
  
  set regPointOld = the regPoint of bitmapMember
  
  -- Temporary import slot
  set total = the number of members of castLib 1
  new(#bitmap, castLib 1, total + 1)
  set tmpMember = member(total + 1) of castLib 1
  
  importFileInto tmpMember, bitmapFileName
  
  if the type of tmpMember = #bitmap then
    set the picture of bitmapMember = the picture of tmpMember
    set the regPoint of bitmapMember = regPointOld
    erase tmpMember
  else
    erase tmpMember
    logMsg("Patch failed: invalid bitmap " & bitmapFileName)
  end if
end

on replaceField fieldMember, textFileName
  set t = the type of fieldMember
  if t <> #field and t <> #text then exit

  if baFileExists(textFileName) = 0 then
    logMsg("File not found: " & textFileName)
    exit
  end if

  set f = new(xtra "FileIO")
  openFile(f, textFileName, 1)

  if status(f) <> 0 then
    logMsg("Error opening file: " & error(f, status(f)))
    closeFile(f)
    exit
  end if

  set textContent = readFile(f)
  closeFile(f)

  if voidp(textContent) or textContent = EMPTY then
    logMsg("File is empty or unreadable: " & textFileName)
    exit
  end if

  -- Clean and overwrite without recreating
  -- TODO not sure if all of this is needed, probably only text is enough
  set the text of fieldMember = EMPTY
  set the editable of fieldMember = FALSE
  set the textFont of fieldMember = "MS Gothic"
  set the textSize of fieldMember = 12
  set the textStyle of fieldMember = "plain"
  set the foreColor of fieldMember = 0
  set the backColor of fieldMember = 255
  set the text of fieldMember = textContent

  -- Not sure if needed to be honest, TODO test if it works without that
  updateStage
  puppetPalette 0
  updateStage
end

-----------------------------------------------
-- UTILITIES
-----------------------------------------------
on removeExtension fileName
  set dotPos = offset(".", fileName)
  if dotPos > 0 then
    set nameNoExt = ""
    repeat with i = 1 to dotPos - 1
      put char i of fileName after nameNoExt
    end repeat
    return nameNoExt
  else
    return fileName
  end if
end

on getFileNameFromPath p
  set lastSlash = 0
  set len = the number of chars in p
  
  repeat with i = 1 to len
    if char i of p = "\" or char i of p = "/" then
      set lastSlash = i
    end if
  end repeat
  
  set result = ""
  if lastSlash > 0 then
    repeat with j = lastSlash + 1 to len
      put char j of p after result
    end repeat
    return result
  else
    return p
  end if
end
