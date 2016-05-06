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
		$client = New-Object System.Net.WebClient
		if (!$client.Proxy.Credentials){
			netsh winhttp import proxy source=ie
			$client.Proxy.Credentials=Get-Credential
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
		Write-Progress -Activity 'Downloading file' -Status $url
		$client.DownloadFileAsync($url, $localFile)
	   
		while (!($Global:downloadComplete)) {                
			$pc = $Global:DPCEventArgs.ProgressPercentage
			if ($pc -ne $null) {
				Write-Progress -Activity 'Downloading file' -Status $url -PercentComplete $pc -CurrentOperation "Transferring"
			}
		}
	   
	    $text = $url + " completed!"
		Write-Progress -Activity 'Downloading file' -Status $url -CurrentOperation "Completed!"
		Start-Sleep 1
		Write-Progress -Activity 'Downloading file' -Status $url -Complete
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



$webclient = new-object System.Net.WebClient
Import-Module BitsTransfer
foreach ($url in $args)  
{
	$f=[System.IO.Path]::GetFileName($url)
	echo $f
	$filename = [System.IO.Path]::GetFileName($url)
	if (Test-Path $filename) {
		$str = "File [" + $filename + "] already exists. Downloading skipped"
		echo $str
	}
	else 
	{
		$IsBypassed=$webClient.Proxy.IsBypassed($url)
		if ($IsBypassed){
			$str = "Downloading (bypass proxy) : " + $url
			echo $str
			Start-BitsTransfer -DisplayName $filename -Source $url -Destination $filename 
		}
		else {
			$str ="Downloading (through proxy): " + $url
			echo $str
			DownloadFile($url)
		}
	}
}