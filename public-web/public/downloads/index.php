<!doctype html>
<html>
<head>
   <meta charset="UTF-8">
   <link rel="shortcut icon" href="favicon.ico">
   <title>ngasp - Releases</title>

   <link rel="stylesheet" href="style/style.css">
   <script src="js/sorttable.js"></script>
   <script language="Javascript">
   function OnLoad() {
        // newTableObject = document.getElementById('TableId');
        // sorttable.makeSortable(newTableObject);

        var o = document.getElementById('VersionTH');
        o.click();
        o.click();
   }
   </script>
   <style>
   </style>

</head>

<body onLoad="javascript:OnLoad()">
<div id="container">
	<h1>ngasp - Releases</h1>

	<table class="sortable" id="TableId">
	    <thead>
		    <tr>
			    <!-- <th>Filename</th> -->
			    <!-- <th>Type</th> -->
                <th>Platform</th>
                <th class="sorttable_numeric" id="VersionTH">Version</th>
                <th>Size</th>
                <th>Release Date</th>
            </tr>
	        </thead>
	    <tbody><?php

	function get_version($file) {
    $version = substr($file, strpos($file, "_") + 1);
    $version = substr($version, 0, strpos($version, "_"));
    return $version;
  }

  function get_platform($file) {
    $platform = "Unknown"; 
    $pos = strrpos($file, "_LINUX");
    if ($pos != false) {
      $platform = "Linux";
    } else {
      $pos = strrpos($file, "_WINDOWS");
      if ($pos != false) {
        $platform = "Windows";
      }
      else {
        $pos = strrpos($file, "_MAC");
        if ($pos != false) {
          $platform = "OS X";
        } else {
            $pos = strrpos($file, "_MP");
            if ($pos != false) {
              $platform = "Multiplatform with Docker";
            } else {
            }
        }
      }
    }
    return $platform;
  }

	// Adds pretty filesizes
	function pretty_filesize($file) {
		$size=filesize("./binaries/" . $file);
/*
		if($size<1024){$size=$size." Bytes";}
		elseif(($size<1048576)&&($size>1023)){$size=round($size/1024, 1)." KB";}
		elseif(($size<1073741824)&&($size>1048575)){$size=round($size/1048576, 1)." MB";}
		else{$size=round($size/1073741824, 1)." GB";}
*/
    $size=round($size/1048576, 1)." MB";

		return $size;
	}



 	// Checks to see if veiwing hidden files is enabled
	if($_SERVER['QUERY_STRING']=="hidden")
	{$hide="";
	 $ahref="./";
	 $atext="Hide";}
	else
	{$hide=".";
	 $ahref="./?hidden";
	 $atext="Show";}

	 // Opens directory
	 $myDirectory=opendir("./binaries");

	// Gets each entry
	while($entryName=readdir($myDirectory)) {
	   $dirArray[]=$entryName;
	}

	// Closes directory
	closedir($myDirectory);

	// Counts elements in array
	$indexCount=count($dirArray);

	// Sorts files
	sort($dirArray);

	// Loops through the array of files
	for($index=0; $index < $indexCount; $index++) {

	// Decides if hidden files should be displayed, based on query above.
	    if(substr("$dirArray[$index]", 0, 1)!=$hide) {

	// Resets Variables
		$favicon="";
		$class="file";

	// Gets File Names
		$name=$dirArray[$index];
		$namehref=$dirArray[$index];

	// Gets Date Modified
		$modtime=date("Y/m/d H:i:s", filemtime("./binaries/" . $dirArray[$index])); /* "M j Y g:i A" */
		$timekey=date("YmdHis", filemtime("./binaries/" . $dirArray[$index]));


	// Separates directories, and performs operations on those directories
		if(is_dir($dirArray[$index]))
		{
				$extn="&lt;Directory&gt;";
				$size="&lt;Directory&gt;";
				$sizekey="0";
				$class="dir";

			// Gets favicon.ico, and displays it, only if it exists.
				if(file_exists("$namehref/favicon.ico"))
					{
						$favicon=" style='background-image:url($namehref/favicon.ico);'";
						$extn="&lt;Website&gt;";
					}

			// Cleans up . and .. directories
				if($name=="."){$name=". (Current Directory)"; $extn="&lt;System Dir&gt;"; $favicon=" style='background-image:url($namehref/.favicon.ico);'";}
				if($name==".."){$name=".. (Parent Directory)"; $extn="&lt;System Dir&gt;";}
		}

	// File-only operations
		else{
			// Gets file extension
			$extn=pathinfo($dirArray[$index], PATHINFO_EXTENSION);

			// Prettifies file type
			switch ($extn){
				case "png": $extn="PNG Image"; break;
				case "jpg": $extn="JPEG Image"; break;
				case "jpeg": $extn="JPEG Image"; break;
				case "svg": $extn="SVG Image"; break;
				case "gif": $extn="GIF Image"; break;
				case "ico": $extn="Windows Icon"; break;

				case "txt": $extn="Text File"; break;
				case "log": $extn="Log File"; break;
				case "htm": $extn="HTML File"; break;
				case "html": $extn="HTML File"; break;
				case "xhtml": $extn="HTML File"; break;
				case "shtml": $extn="HTML File"; break;
				case "php": $extn="PHP Script"; break;
				case "js": $extn="Javascript File"; break;
				case "css": $extn="Stylesheet"; break;

				case "pdf": $extn="PDF Document"; break;
				case "xls": $extn="Spreadsheet"; break;
				case "xlsx": $extn="Spreadsheet"; break;
				case "doc": $extn="Microsoft Word Document"; break;
				case "docx": $extn="Microsoft Word Document"; break;

				case "zip": $extn="ZIP Archive"; break;
				case "htaccess": $extn="Apache Config File"; break;
				case "exe": $extn="Windows Executable"; break;

				default: if($extn!=""){$extn=strtoupper($extn)." File";} else{$extn="Unknown";} break;
			}

			// Gets and cleans up file size
				$size=pretty_filesize($dirArray[$index]);
				$sizekey=filesize($dirArray[$index]);
        $platform=get_platform($name);
        $version=get_version($name);
        list($ver1, $ver2, $ver3) = split('[.]', $version);
        $ver1 = $ver1*1000000;
        $ver2 = $ver2*10000;  
        $ver3 = $ver3*1;
        $versionkey = $ver1 + $ver2 + $ver3;
		}

	// Output
    /*
    <tr class='$class'>
        <td>
            <a href='./binaries/$namehref'>$name</a>
        </td>
        <td>
            <a href='./$namehref'>$extn</a>
        </td>
        <td>
            <a href='./binaries/$namehref'>$platform</a>
        </td>
        <td>
            <a href='./binaries/$namehref'>$version</a>
        </td>
        <td>
            <a href='./binaries/$namehref'>$size</a>
        </td>
        <td sorttable_customkey='$timekey'>
            <a href='./binaries/$namehref'>$modtime</a>
        </td>
    </tr>
    */
if ($version != "release") {
	 echo("


<tr class='$class'>
    <td sorttable_customkey='$platform'>
        <a href='./binaries/$namehref'>$platform</a>
    </td>
    <td sorttable_customkey='$versionkey'>
        <a href='./binaries/$namehref'>$version</a>
    </td>
    <td sorttable_customkey='$sizekey'>
        <a href='./binaries/$namehref'>$size</a>
    </td>
    <td sorttable_customkey='$modtimekey'>
        <a href='./binaries/$namehref'>$modtime</a>
    </td>
</tr>
");
}
	   }
	}
	?>

	    </tbody>
	</table>

  <br />
	<!-- <h2><?php echo("<a href='$ahref'>$atext hidden files</a>"); ?></h2> -->

</div>
<br />
<div>
Copyright (c) 2009-2017, Sebastián Ramos Onsins. Centre for Research in Agricultural Genomics. All rights reserved.
<br />
ngasp is licensed under the <a href="https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html">LGPL version 2.1 license</a>.
</div>

</body>
</html>
