$buildPath = "C:\Users\school\Documents\Hawata\build"
if (Test-Path $buildPath) {
    Write-Host "Removing build directory..."
    Remove-Item -Recurse -Force $buildPath -ErrorAction Stop
    Write-Host "Build directory removed successfully"
} else {
    Write-Host "Build directory does not exist"
}
Write-Host "Done"
