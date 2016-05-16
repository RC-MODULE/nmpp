<#
.SYNOPSIS
    Downloads a file showing the progress of the download
.DESCRIPTION
    This Script will download a file locally while showing the progress of the download
.EXAMPLE
    .\Download-File.ps1 'http:\\someurl.com\somefile.zip'
.EXAMPLE
    .\Download-File.ps1 'http:\\someurl.com\somefile.zip' 'C:\Temp\somefile.zip'
.PARAMETER url
    url to be downloaded
.PARAMETER localFile
    the local filename where the download should be placed
.NOTES
    FileName     : Download-File.ps1
    Author       : CrazyDave
#Requires -Version 2.0
#>
Function DownloadFile  {
	param(
		[Parameter(Mandatory=$true)]
		[String] $url,
		[Parameter(Mandatory=$false)]
		[String] $localFile = (Join-Path $pwd.Path $url.SubString($url.LastIndexOf('/')))
		
	)

	begin {	   
	
		[Net.ServicePointManager]::ServerCertificateValidationCallback = {$true}
		$client = New-Object System.Net.WebClient
		$IsBypassed=$client.Proxy.IsBypassed($url)
		if (!$IsBypassed){
			if (!$client.Proxy.Credentials){
				netsh winhttp import proxy source=ie
				$client.Proxy.Credentials=Get-Credential
			}
		}
		
		$Global:downloadComplete = $false
		
		$eventDataComplete = Register-ObjectEvent $client DownloadFileCompleted `
			-SourceIdentifier WebClient.DownloadFileComplete `
			-Action {$Global:downloadComplete = $true}
		$eventDataProgress = Register-ObjectEvent $client DownloadProgressChanged `
			-SourceIdentifier WebClient.DownloadProgressChanged `
			-Action { $Global:DPCEventArgs = $EventArgs }    
	}	

	process {
		
		#echo ** $url **
		#echo ** $localFile **
		if ($url.StartsWith("https")){
			#echo $url sync
			Write-Progress -Activity 'Downloading file' -Status $url
			$client.DownloadFile($url, $localFile)
		}
		else 
		{
			#echo $url async
			Write-Progress -Activity 'Downloading (async) file' -Status $url
			$client.DownloadFileAsync($url, $localFile)
			while (!($Global:downloadComplete)) {                
				$pc = $Global:DPCEventArgs.ProgressPercentage
				if ($pc -ne $null) {
					Write-Progress -Activity 'Downloading (async) file' -Status $url -PercentComplete $pc -CurrentOperation "Transferring"
				}
			}
		}
		if ((Test-Path $localFile) -and ( (Get-Item $localFile).length -eq 0)) {
			Write-Progress -Activity 'Retry to download file' -Status $url
			$client.DownloadFile($url, $localFile)
		}
		if ((Test-Path $localFile) -and ( (Get-Item $localFile).length -gt 0)) {
			$text = $url + " completed!"
			Write-Progress -Activity 'Downloading file' -Status $url -CurrentOperation "Completed!"
			Start-Sleep 1
			Write-Progress -Activity 'Downloading file' -Status $url -Complete	
		}
		else {
			$text = $url + " Failed!"
			Write-Progress -Activity 'Downloading file' -Status $url -CurrentOperation "Failed!"
			Start-Sleep 1
			Write-Progress -Activity 'Downloading file' -Status $url -Complete	
		}
	    
	}
	
	end {	
		Unregister-Event -SourceIdentifier WebClient.DownloadProgressChanged
		Unregister-Event -SourceIdentifier WebClient.DownloadFileComplete
		$client.Dispose()
		$Global:downloadComplete = $null
		$Global:DPCEventArgs = $null
		Remove-Variable client
		Remove-Variable eventDataComplete
		Remove-Variable eventDataProgress
		[GC]::Collect()    
	}
}


foreach ($url in $args)  
{
	$filename = [System.IO.Path]::GetFileName($url)
	if ((Test-Path $filename) -and ( (Get-Item $filename).length -gt 0)) {
		$str = "File [" + $filename + "] already exists. Downloading skipped"
		echo $str
	}
	else 
	{
		$str ="Start downloading: " + $url 
		echo $str
		DownloadFile $url 
	}
}