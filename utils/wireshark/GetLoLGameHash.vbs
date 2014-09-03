Option Explicit

Dim objWMIService, colItems, objItem, myRegExp, objFS, objFile, found, base64Regex, myMatches, myMatch

Sub PrintOut ( msg )
	If Not LCase( Right( WScript.FullName, 12 ) ) = "\cscript.exe" Then
		Wscript.Echo ( msg )
	Else
		WScript.StdOut.Write ( msg )
	End If
End Sub

found = False

Set myRegExp = New RegExp
myRegExp.IgnoreCase = True
myRegExp.Pattern = """ "".*== [0-9]+"

Set base64Regex = New RegExp
base64Regex.Pattern = "[a-zA-Z0-9+/]{22}=="

Set objWMIService = GetObject( "winmgmts://./root/cimv2" )

Set colItems = objWMIService.ExecQuery( "Select CommandLine, ExecutablePath, Name from Win32_Process Where Name='League of Legends.exe'", , 32 )

For Each objItem in colItems
    
    If myRegExp.test( objItem.CommandLine ) then
	
	'Set objFS = CreateObject("Scripting.FileSystemObject")
	'Set objFile = objFS.OpenTextFile("GetLoLGameHash.log", 8, True)
	'objFile.WriteLine now & vbTab & objItem.CommandLine
	'objFile.Close

	Set myMatches = base64Regex.Execute( objItem.CommandLine )
	For Each myMatch in myMatches
		PrintOut( myMatch.Value )
		found = True
	Next
    
    End If

Next

If found = False Then
	PrintOut( "No instance of 'League of Legends.exe' found..." )
End If
