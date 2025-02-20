# Get all subdirectories recursively, but only rename the folder containing the .ino file
Get-ChildItem -Path . -Directory -Recurse | ForEach-Object {
    $folderPath = $_.FullName
    $parentFolder = Split-Path -Parent $folderPath

    # Find the first .ino file inside this folder (if exists)
    $inoFile = Get-ChildItem -Path $folderPath -Filter "*.ino" -File | Select-Object -First 1

    if ($inoFile) {
        # Extract the base names
        $fileName = $inoFile.Name
        $folderName = $_.Name

        # Trim names from the first '-'
        $trimmedFileName = $fileName -replace "-.*", ""
        $trimmedFolderName = $folderName -replace "-.*", ""

        # Rename the .ino file if needed
        if ($trimmedFileName -ne $fileName) {
            $newFilePath = Join-Path $folderPath "$trimmedFileName.ino"
            Rename-Item -Path $inoFile.FullName -NewName "$trimmedFileName.ino"
            Write-Host "Renamed file: $fileName -> $trimmedFileName.ino"
        }

        # Rename only the folder containing the .ino file, keeping its parent folder unchanged
        if ($trimmedFolderName -ne $folderName) {
            $newFolderPath = Join-Path $parentFolder $trimmedFolderName
            Rename-Item -Path $folderPath -NewName $trimmedFolderName
            Write-Host "Renamed folder: $folderName -> $trimmedFolderName"
        }
    }
}
