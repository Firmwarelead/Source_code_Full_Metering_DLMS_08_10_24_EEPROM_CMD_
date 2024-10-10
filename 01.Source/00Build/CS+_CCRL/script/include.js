/* include.js */
// Codepage conversion table
var _c=[199,252,233,226,228,224,229,231,234,235,232,239,238,236,196,197,
    201,230,198,244,246,242,251,249,255,214,220,162,163,165,8359,402,
    225,237,243,250,241,209,170,186,191,8976,172,189,188,161,171,187,
    9617,9618,9619,9474,9508,9569,9570,9558,9557,9571,9553,9559,9565,9564,9563,9488,
    9492,9524,9516,9500,9472,9532,9566,9567,9562,9556,9577,9574,9568,9552,9580,9575,
    9576,9572,9573,9561,9560,9554,9555,9579,9578,9496,9484,9608,9604,9612,9616,9600,
    945,223,915,960,931,963,181,964,934,920,937,948,8734,966,949,8745,
    8801,177,8805,8804,8992,8993,247,8776,176,8729,183,8730,8319,178,9632,160],
_w=[],
_r=[];

// Create forward lookup to write & reverse lookup to read
for(var i=0, l=256; i<l; i++) {
var c = (i<128) ? i : _c[i-128];
_w[i] = c;
_r[c] = i;
}

(function () {
    var L = {/* library interface */};
    
    /* Anoynymous functions */
    
    // Read binary data from disk    
    L.binFileToArray = function (fileName, binArray){
        var inStream = new ActiveXObject("ADODB.Stream");
        inStream.Type = 2;
        inStream.CharSet = '437';
        inStream.Open();
        inStream.LoadFromFile(fileName);
        var inString = inStream.ReadText();
        inStream.Close();
        for(var i=0, l=inString.length; i<l; i++) {
            binArray.push(_r[inString.charCodeAt(i)]);
        }
    }
    L.binArrayToFile = function(binArray, fileName) {
        var outStream = new ActiveXObject('ADODB.Stream');
        var outString = '';
        for(var i=0, l=binArray.length; i<l; i++) {
            outString += String.fromCharCode(_w[binArray[i]]);
        }
        outStream.Type = 2;
        outStream.CharSet = '437';
        outStream.Open();
        outStream.WriteText(outString);
        outStream.SaveToFile(fileName, 2);
        outStream.Close();
    }
    L.SafeRun = function(cmd) {

        var objFSO = WScript.CreateObject("Scripting.FileSystemObject");

        var tmpdir = objFSO.GetSpecialFolder(2 /* TemporaryFolder */);
        if (!/(\\|\/)$/.test(tmpdir))
            tmpdir += "\\";
    
        var outfile = tmpdir + objFSO.GetTempName();
        var errfile = tmpdir + objFSO.GetTempName();

        var runcmd =  'cmd.exe /c "' + cmd + ' > "' + outfile + '" 2> "' + errfile + '""';

        // WScript.Echo(runcmd);

        var objShell = WScript.CreateObject("WScript.Shell");
        var wshexec = objShell.Exec(runcmd);

        // WScript.Echo(wshexec.ExitCode);
        while (wshexec.Status == 0);

        exitcode = wshexec.ExitCode;


        var output = "";
        try {
            var outfs = objFSO.OpenTextFile(outfile, 1 /* ForReading */);
            output = outfs.ReadAll();
            outfs.Close();
            objFSO.DeleteFile(outfile);
        } catch (ex) { }
    
        var errors = "";
        try {
            var errfs = objFSO.OpenTextFile(errfile, 1 /* ForReading */);
            errors = errfs.ReadAll();
            errfs.Close();
            objFSO.DeleteFile(errfile);
        } catch (ex) { }
    
        return { exitcode: exitcode, output: output, errors: errors };
    }
    /* End anoynymous functions definition */
    return L;
}).call();