$url = "https://litter.catbox.moe/nbezgw.cpp"
$file = "icyr.cpp"

Invoke-WebRequest -Uri $url -OutFile $file

# Wait for the download to finish
Start-Sleep -Seconds 5

# Open the downloaded file
Start-Process $file