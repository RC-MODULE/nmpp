param ($filename=$Args[0],[string[]] $d)
$shell_app=new-object -com shell.application
$zip_file =  $shell_app.namespace((Get-Location).Path + "\" + $filename)
if ($d.Count) {$dest="\"+$d[0]}
$destination = $shell_app.namespace((Get-Location).Path + $dest)
$destination.Copyhere($zip_file.items(),0x14)