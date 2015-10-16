$webclient = new-object System.Net.WebClient
$IsBypassed=$webClient.Proxy.IsBypassed("http://module.ru")
if ($IsBypassed){
	Import-Module BitsTransfer
}
else {
	netsh winhttp import proxy source=ie
	$creds=Get-Credential
	$webclient.Proxy.Credentials=$creds
}

foreach ($url in $args)  
{
	$filename = [System.IO.Path]::GetFileName($url)
	$str = "downloading " + $url 
	echo $str
	if ($IsBypassed){
		Start-BitsTransfer -DisplayName $filename -Source $url -Destination $filename 
	}
	else {
		$webclient.DownloadFile($url,$filename)
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

