$webclient = new-object System.Net.WebClient
Import-Module BitsTransfer
foreach ($url in $args)  
{
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
			if (!$webclient.Proxy.Credentials){
				netsh winhttp import proxy source=ie
				$webclient.Proxy.Credentials=Get-Credential
			}
			$str ="Downloading (through proxy): " + $url
			echo $str
			$webclient.DownloadFile($url,$filename)
		}
	}
}










#param ($url=$Args[0])
#$proxy = new-object System.Net.WebProxy "proxy:80"
#$proxy.Credentials = $creds
#$proxy.Credentials = New-Object System.Net.NetworkCredential ($env:USERNAME, $env:PASSWORD)
#$proxy = [System.Net.WebRequest]::GetSystemWebProxy()
#$proxy.Credentials = [System.Net.CredentialCache]::DefaultCredentials
#$proxy.useDefaultCredentials = $true
#$webclient.proxy=$proxy
#$webclient.DownloadFile( "http://savepic.ru/7691336.png","7691336.png")

