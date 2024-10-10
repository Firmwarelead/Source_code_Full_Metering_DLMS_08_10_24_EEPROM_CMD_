
// Common variables for all functions below
var g_objFSO = WScript.CreateObject("Scripting.FileSystemObject");
var Lib = eval(g_objFSO.OpenTextFile(g_objFSO.GetParentFolderName(WScript.ScriptFullName) + "\\include.js", 1).ReadAll());
var verbose;

// Follow format of CS+ to parse accordingly:
//  message-type 05 message-number : message
//  Message type:
//      E: error
//      W: warning
//  Message number: The message numbers when the CC-RL is executed are 5 digits number output following number (05).
var g_msg_dict = {
    "E_FileNotFound":"E0500001: File not found. ",
    "E_IncorrectFormat":"E0500002: Incorrect format. ",
    "E_LengthUnmatched":"E0500003: Length un-matched. ",
    "W_StringOutRange":"W0500001: Input string out range, truncation occurred. ",
    "":""  //Final element
};

function get_windows_separator_path(input_path){
    return input_path.replace(/\//g, '\\');
}

/* Class like functions */
function InputArgs() {
    this.PartitionSetting = function()
    {
        var Used;
        var AbsPath;
        var StrHexAddressRange;
        var FileName;
        var IntStartAddress;
        var IntEndAddress;
        var IntShiftStartAddress;
        var StrShiftStartAddress;
        var MotFilePath;
        var MotFilePathRewritebank;
    }
    this.UserPartitionSetting = function() 
    {
        var Used;
        var AbsPath;
        var StrHexAddressRange;
        var FileName;
        var IntStartAddress;
        var IntEndAddress;
        var IntShiftStartAddress;
        var StrShiftStartAddress;
        var MotFilePath;
        var MotFilePathRewritebank;
        var StrHexAddressRangeWithHeader;
        var IntCodeSizeWithHeader;
        var StrHexAddressRangeNoHeader;
        var IntCodeSizeNoHeader;
    }

    this.LinkerPath;
    this.UserAppLinkerOptionFilePath;
    this.ImageHeaderFilePath;
    this.ImageFolderPath;
    this.ImageIdentifierStr;
    this.ImageSoftwareVersionStr;
    this.ImageSoftwareVersionValue;
    this.DeviceSizeStr;
    this.DeviceSizeInt;
    this.BootloaderInfo = new this.PartitionSetting();
    this.UserAppInfo = new this.UserPartitionSetting();
    this.FixedMetrologyInfo = new this.PartitionSetting();

    this.TransferImageFilePath;
    this.ProductionImageFilePath;
    this.ProductionImageFilePathCurrentbank;
    this.ProductionImageFilePathRewritebank;

    this._parsing_image_identifier = function(str_identifier) {
        // Assign to string identifier for later use
        this.ImageIdentifierStr = str_identifier;
    }

    this._parsing_version = function(str_version) {
        this.ImageSoftwareVersionStr = str_version;
        this.ImageSoftwareVersionValue = parseInt(this.ImageSoftwareVersionStr);
    }

    this._parsing_device_size = function(device_size) {
        this.IntDeviceSize = parseInt(device_size);
        this.StrDeviceSize = this.IntDeviceSize.toString("16");
    }

    this._parsing_partition_setting = function(setting, partition_info) {
        partition_info.Used = (setting != null);
        if (partition_info.Used == true)
        {
            // Split setting part for abs path and address range setting
            this.split_setting(setting, partition_info);
            // Check address_range and calculate rewrite bank address_range
            this.check_and_caculate_address_range(partition_info);
            // Make output path of mot file
            this.make_mot_file_path(partition_info);
        }
    }
    this._parsing_user_partition_setting = function(setting, partition_info, image_header) {
        this._parsing_partition_setting(setting, partition_info)

        // From parse user app range and header size, calculate the actual user code range
        // This would be used later for CRC calculation and output user application binary file
        var objCCRL = new CCRL_Helper();
        partition_info.IntCodeSizeWithHeader = objCCRL.calculate_abs_built_rom_size(this.LinkerPath, partition_info.AbsPath, partition_info.StrHexAddressRange);
        partition_info.IntCodeSizeNoHeader = partition_info.IntCodeSizeWithHeader - image_header.HEADER_SIZE;
        var user_app_code_end_address = partition_info.IntStartAddress + partition_info.IntCodeSizeWithHeader - 1;

        var user_app_code_start_address = partition_info.IntStartAddress;
        partition_info.StrHexAddressRangeWithHeader = user_app_code_start_address.toString("16") + "-" + user_app_code_end_address.toString("16");

        var user_app_crc_start_address = partition_info.IntStartAddress + image_header.HEADER_SIZE;
        partition_info.StrHexAddressRangeNoHeader = (user_app_crc_start_address).toString("16") + "-" + user_app_code_end_address.toString("16");
    }

    this._parsing_image_output_path = function(image_path, transfer_name, production_name) {
        this.TransferImageFilePath = g_objFSO.BuildPath(image_path, transfer_name + ".bin");
        this.ProductionImageFilePath = g_objFSO.BuildPath(image_path, production_name + ".mot");
        this.ProductionImageFilePathCurrentbank = g_objFSO.BuildPath(image_path, production_name + "0.mot");
        this.ProductionImageFilePathRewritebank = g_objFSO.BuildPath(image_path, production_name + "1.mot");
    }

    this.split_setting = function(str_setting, out_setting_info) {
        if (str_setting != null && out_setting_info != null) {
            var PARTITION_SETTING_DELIMITER = "/";

            var setting_array = [
                str_setting.split(PARTITION_SETTING_DELIMITER).slice(0,-1).join(PARTITION_SETTING_DELIMITER),   //rest
                str_setting.split(PARTITION_SETTING_DELIMITER).pop()    //last
            ]
            /* Catch error if there's delimiter not available causing second element null */
            if (setting_array[1] == null){
                throw new Error(g_msg_dict.E_IncorrectFormat + str_setting + " (\"" + PARTITION_SETTING_DELIMITER + "\" delimiter not found)");
            }
    
            out_setting_info.AbsPath = get_windows_separator_path(setting_array[0]);
            out_setting_info.StrHexAddressRange = setting_array[1];
        }
    }

    this.check_and_caculate_address_range = function(in_out_setting_info) {
        if (in_out_setting_info != null) {
            var ADDRESS_RANGE_DELIMITER = "-";

            // Try splitting the start and end address
            var address_array = in_out_setting_info.StrHexAddressRange.split(ADDRESS_RANGE_DELIMITER);

            // Catch error if there's delimiter not available causing second element null
            if (address_array[1] == null) {
                throw new Error(g_msg_dict.E_IncorrectFormat + in_out_setting_info.StrHexAddressRange + " (\"" + ADDRESS_RANGE_DELIMITER + "\" delimiter not found)");
            }
            
            in_out_setting_info.IntStartAddress = parseInt("0x" + address_array[0]);
            in_out_setting_info.IntEndAddress = parseInt("0x" + address_array[1]);

            // Calculate shift address:
            //  For dual bank, shift address is half of device size + start address
            in_out_setting_info.IntShiftStartAddress = (this.IntDeviceSize / 2) + in_out_setting_info.IntStartAddress;
            in_out_setting_info.StrShiftStartAddress = in_out_setting_info.IntShiftStartAddress.toString("16");
        }
    }

    this.make_mot_file_path = function(in_out_setting_info) {
        if (in_out_setting_info != null) {
            //Get file name
            in_out_setting_info.FileName = g_objFSO.GetBaseName(in_out_setting_info.AbsPath);
            in_out_setting_info.MotFilePathCurrentbank = g_objFSO.BuildPath(this.ImageFolderPath, in_out_setting_info.FileName + "0.mot");
            in_out_setting_info.MotFilePathRewritebank = g_objFSO.BuildPath(this.ImageFolderPath, in_out_setting_info.FileName + "1.mot");
        }
    }

    this._check_file_exists = function(in_str_path) {
        if (in_str_path != null) {
            if (g_objFSO.FileExists(in_str_path) == 0) {
                throw new Error(g_msg_dict.E_FileNotFound + in_str_path);
            }
        }
    }

    this._check_folder_exists = function(in_str_path)
    {
        if (in_str_path != null) {
            if (g_objFSO.FolderExists(in_str_path) == 0) {
                g_objFSO.CreateFolder(in_str_path);
            } else {
            }
        }
    }

    // Check if path existed
    this.Parse = function (linker, user_clnk, header, image, transfer_name, production_name, platform, version, device_size, setting_bootloader, setting_user, setting_metrology, image_header) {
        // Simple arguments: assigning directly or just few line        
        this.LinkerPath = get_windows_separator_path(linker);
        this.UserAppLinkerOptionFilePath = get_windows_separator_path(user_clnk);
        this.ImageHeaderFilePath = header;
        this.ImageFolderPath = get_windows_separator_path(image);
        
        // More step parsing arguments
        this._parsing_image_identifier(platform);
        this._parsing_version(version);
        this._parsing_device_size(device_size);
        this._parsing_user_partition_setting(setting_user, this.UserAppInfo, image_header);
        this._parsing_partition_setting(setting_bootloader, this.BootloaderInfo);
        this._parsing_partition_setting(setting_metrology, this.FixedMetrologyInfo);
        this._parsing_image_output_path(this.ImageFolderPath, transfer_name, production_name);

        // Validating file path
        this._check_file_exists(this.LinkerPath);
        this._check_file_exists(this.UserAppInfo.AbsPath);
        this._check_file_exists(this.BootloaderInfo.AbsPath);
        this._check_file_exists(this.FixedMetrologyInfo.AbsPath);
        this._check_file_exists(this.ImageHeaderFilePath);

        // Validating folder path (if not exist, then create)
        this._check_folder_exists(this.ImageFolderPath);
    }
}

function CCRL_Helper() {
    /**
     * Generate crc hash binary data of an input absolute file
     * Calculation method is fixed with CRC_METHOD
     * using CCRL rlink tool and final 2 byte of 1MByte RL78 address range to store the CRC output (assume 16bit CRC result)
     */
    this.calculate_crc_from_abs_file = function(linker_path, abs_file_path, str_hex_address_range) {
        var CRC_METHOD = "16-CCITT-LSB:LITTLE";

        if (verbose) WScript.Echo("Calculating CRC for abs file path: " + abs_file_path);

        if (abs_file_path != null)
        {
            var tmpfile = "temp.bin";
            var cmd = "\"" + linker_path +"\"" + " \"" + abs_file_path + "\"" + " -output="+tmpfile+"=ffffe-fffff" + " -form=binary" + " -crc=ffffe=" + str_hex_address_range + "/" + CRC_METHOD + " -space=ff" + " -NOLOgo";
            WScript.Echo(cmd);

            var result = Lib.SafeRun(cmd);
            
            //seems that rlink.exe output to error stream 
            WScript.Echo(result.errors);

            //Read the output file
            var crc_array = new Array();
            Lib.binFileToArray(tmpfile, crc_array);
            
            //Remove the temporary file
            g_objFSO.DeleteFile(tmpfile);
            
            var crc_value = crc_array[1] << 8 | crc_array[0];
            var crc_string = "0x" + crc_value.toString("16");

            return {crc_array:crc_array, crc_value:crc_value, crc_string:crc_string};
        }
    }

    /**
     * Calculate size of built absolute file by calculate the generated binary file size
     * Required CCRL V1.0.7 and above
     */
    this.calculate_abs_built_rom_size = function(linker_path, abs_file_path, str_hex_address_range) {
        // set cmd="%Linker%" "%UserAppAbsoluteFile%" -output="temp.bin"=%UserAppRange% -form=binary -NOLOgo
        if (verbose) WScript.Echo("Calculating built ROM size from abs file: " + abs_file_path);

        var tmpfile = "temp.bin";
        var cmd = "\"" + linker_path +"\"" + " \"" + abs_file_path + "\"" + " -output="+tmpfile+"="+str_hex_address_range + " -form=binary" + " -NOLOgo";
        WScript.Echo(cmd);

        var result = Lib.SafeRun(cmd);
        
        // Seems that rlink.exe output to error stream 
        WScript.Echo(result.errors);
            
        // Read file size
        var file_size = g_objFSO.GetFile(tmpfile).Size;
        
        // Remove the temporary file
        g_objFSO.DeleteFile(tmpfile);

        var aligned_file_size = (parseInt((file_size + 3) / 4) * 4)
        WScript.Echo("Calculated user app size: " + file_size.toString("16") + "(hex) "  + file_size.toString() + "(dec)");
        WScript.Echo("Aligned 4byte size      : " + aligned_file_size.toString("16") + "(hex) "  + aligned_file_size.toString() + "(dec)");

        return aligned_file_size;
    }

    /**
     * CCRL linker when running will output all linker options to clnk file
     * Using that file, program linking can be done when using option -subcommand
     */
    this.link_with_clnk_file = function(linker_path, clnk_file_path) {
        if (verbose) WScript.Echo("Link with clnk file (using subcommand): " + clnk_file_path);

        var cmd = "\"" + linker_path +"\"" + " -subcommand=" + "\"" + clnk_file_path + "\"";
        WScript.Echo(cmd);
        
        var result = Lib.SafeRun(cmd);

        //seems that rlink.exe output to error stream 
        WScript.Echo(result.errors);
    }

    /** 
     * Hex file output (output format Motorola S-record) from abs file
     */
    this.output_mot_file_from_abs = function(linker_path, abs_file_path, output_file_path, str_hex_address_range, str_shift_address) {
        // Ex:"%Program%" "%MainProjectDir%\%BuildModeName%\rl78i1c.abs" -output="%MainProjectDir%\%BuildModeName%\rl78i1c_user_app1.mot"=0c000-3ffff/4c000 -form=stype -NOLOgo
        if (verbose) WScript.Echo("Output mot file from abs file: " + abs_file_path);

        if (str_shift_address == null) {
            str_shift_address = "";
        } else {
            str_shift_address = "/" + str_shift_address;
        }
        var cmd = "\"" + linker_path +"\"" + " \"" + abs_file_path + "\"" + " -output="+"\""+output_file_path+"\""+"="+str_hex_address_range + str_shift_address + " -form=stype" + " -NOLOgo";
        WScript.Echo(cmd);
        
        var result = Lib.SafeRun(cmd);

        //seems that rlink.exe output to error stream 
        WScript.Echo(result.errors);
    }

    /** 
     * Concatenate hex file
     */
    this.concatenate_mot_file = function(linker_path, output_file_path, array_mot_file_path) {
        //  Ex:"%Program%" -output="%MainProjectDir%\%BuildModeName%\Image\rl78i1c_production0.mot" -form=stype "%MainProjectDir%\%BuildModeName%\Image\rl78i1c_user_app.mot" "%MainProjectDir%\..\rl78i1c\bootloader\bootloader.mot" "%MainProjectDir%\..\rl78i1c\middleware\em_middleware.mot" -NOLOgo
        if (verbose) WScript.Echo("Concatenating mot file: " + array_mot_file_path);

        var cmd = "\"" + linker_path +"\"" + " -output="+"\""+output_file_path+"\"" + " -form=stype" + " -NOLOgo";
        var i;
        for (i = 0; i < array_mot_file_path.length; i++) {
            cmd += " \"" + array_mot_file_path[i] + "\"";
        }

        WScript.Echo(cmd);
        
        var result = Lib.SafeRun(cmd);

        //seems that rlink.exe output to error stream 
        WScript.Echo(result.errors);
    }
    /**
     * Generate binary file
     */
    this.output_binary_file_from_abs = function(linker_path, abs_file_path, output_file_path, str_hex_address_range, str_shift_address) {
        if (verbose) WScript.Echo("Output binary file from abs file: " + abs_file_path);

        if (str_shift_address == null) {
            str_shift_address = "";
        } else {
            str_shift_address = "/" + str_shift_address;
        }
        var cmd = "\"" + linker_path +"\"" + " \"" + abs_file_path + "\"" + " -output="+"\""+output_file_path+"\""+"="+str_hex_address_range + str_shift_address + " -form=binary -space=ff" + " -NOLOgo";
        WScript.Echo(cmd);
        
        var result = Lib.SafeRun(cmd);

        //seems that rlink.exe output to error stream 
        WScript.Echo(result.errors);
    }
}

function ImageHeader() {
    this.HEADER_SIZE = 256;
    
    //Below is each element inside the header
    this.IdentifierArr = new Array(32);
    this.SoftwareVersionArr = new Array(4);
    this.UserAppSizeArr = new Array(4);
    this.UserAppHashArr = new Array(4);
    this.TransferDateTimeArr = new Array (8);
    this.ActivateDateTimeArr = new Array (8);

    this.UserAppSizeValue;

    this._HeaderInfo = function(header_size) {
        this.raw_data = new Array(header_size);
        this.pos;
    }

    this._set_uint_to_array = function(arr, pos, uint, uint_len) {
        var i;
        if ((pos + uint_len) <= arr.length) {
            for (i = 0; i < uint_len; i++) {
                arr[i] = (uint >>> (i * 8)) & 0xFF;
            }
        } else {
            throw new Error(g_msg_dict.E_LengthUnmatched + "_set_uint16_to_array out of array. " + "lengh: " + arr.length + "pos: " + pos + "uint_len: " + uint_len);
        }
    }
    
    this._date_to_array = function(dt) {
        return new Array(
            dt.getSeconds(),
            dt.getMinutes(),
            dt.getHours(),
            dt.getDate(),
            dt.getDay(),
            dt.getMonth() + 1,
            dt.getFullYear() & 0xFF,
            dt.getFullYear() >>> 8
        );
    }

    /**
     * Initializing image header by filling 0xFF to whole array
     */
    this._initialize_header_info = function(header_info) {
        var i;
        header_info.pos = 0;
        for (i = 0; i < header_info.raw_data.length; i++) {
            header_info.raw_data[i] = 0xFF;
        }
    }

    this._fill_header_info_with_array = function(header_info, arr) {
        var i;
        if (header_info.pos + arr.length <= header_info.raw_data.length)
        {
            for (i = 0; i < arr.length; i++) {
                header_info.raw_data[header_info.pos] = arr[i];
                header_info.pos++;
            }
        } else {
            throw new Error(g_msg_dict.E_LengthUnmatched + "_fill_header_info_with_array overflow. " + "header len: " + header_info.raw_data.length + "header_pos: " + header_info.pos + "array length: " + arr.length);
        }
    }

    this._skip_header_info_number_of_byte = function(header_info, byte_to_skip) {
        header_info.pos += byte_to_skip;
    }

    /**
     * Set image identifier array
     * Input: string type identifier
     * Any ASCII char out of 32 bytes will be truncate
     */
    this.SetIdentifier = function (str_identifier) {
        // Convert string to byte array
        var length = str_identifier.length;
        var i;

        if (verbose) WScript.Echo("SetIdentifier input" + str_identifier);

        if (length > str_identifier.length) {
            length = str_identifier.length;
            WScript.Echo(g_msg_dict.W_StringOutRange + "SetIdentifier input " + str_identifier + "length :" + str_identifier.length);
        }
    
        // Assign each ASCII char to array
        for (i = 0; i < length; i++) {
            this.IdentifierArr[i] = str_identifier.charCodeAt(i);
        }

        if (verbose) WScript.Echo("SetIdentifier output array" + this.IdentifierArr);

    
        // Fill remaining with 0
        for (;i < this.IdentifierArr.length; i++) {
            this.IdentifierArr[i] = 0;
        }
    }

    /**
     * Set software version information
     * Input: Integer number (LSB)
     * Note: 4LSByte pick up to array
     */
    this.SetSoftwareVersion = function(uint_version) {
        this._set_uint_to_array(this.SoftwareVersionArr, 0, uint_version, this.SoftwareVersionArr.length);
    }

    /**
     * Set image size
     */
    this.SetUserAppSize = function(uint_size) {
        this.UserAppSizeValue = uint_size - this.HEADER_SIZE;
        this._set_uint_to_array(this.UserAppSizeArr, 0, this.UserAppSizeValue, this.UserAppSizeArr.length);
    }

    this.GetUserAppSize = function() {
        return this.UserAppSizeValue;
    }

    /**
     * Set user app hash
     */
    this.SetUserAppHash = function(uint_hash) {
        this._set_uint_to_array(this.UserAppHashArr, 0, uint_hash, this.UserAppHashArr.length);
    }

    /**
     * Set transfer date time
     */
    this.SetTransferDateTime = function(dt) {
        var arr_dt = this._date_to_array(dt);
        Array.prototype.splice.apply(this.TransferDateTimeArr, [0, arr_dt.length].concat(arr_dt));
    }

    /**
     * Set activate date time
     */
    this.SetActivateDateTime = function(dt) {
        var arr_dt = this._date_to_array(dt);
        Array.prototype.splice.apply(this.ActivateDateTimeArr, [0, arr_dt.length].concat(arr_dt));
    }

    /**
     * Get complete image header
     */
    this.GetImageHeader = function() {
        var hd = new this._HeaderInfo(this.HEADER_SIZE);
        this._initialize_header_info(hd);
        this._fill_header_info_with_array(hd, this.IdentifierArr);
        this._fill_header_info_with_array(hd, this.SoftwareVersionArr);
        this._fill_header_info_with_array(hd, this.UserAppSizeArr);
        this._fill_header_info_with_array(hd, this.UserAppHashArr);
        this._fill_header_info_with_array(hd, this.TransferDateTimeArr);
        this._fill_header_info_with_array(hd, this.ActivateDateTimeArr);

        return hd.raw_data;
    }

    /**
     * Get image header for transfer
     */
    this.GetTransferImageHeader = function() {
        var hd = new this._HeaderInfo(this.HEADER_SIZE);
        // For transfer image, mask off software version, transfer and activation date time
        this._initialize_header_info(hd);
        this._fill_header_info_with_array(hd, this.IdentifierArr);
        this._skip_header_info_number_of_byte(hd, this.SoftwareVersionArr.length);
        this._fill_header_info_with_array(hd, this.UserAppSizeArr);
        this._fill_header_info_with_array(hd, this.UserAppHashArr);
        this._skip_header_info_number_of_byte(hd, this.TransferDateTimeArr.length);
        this._skip_header_info_number_of_byte(hd, this.ActivateDateTimeArr.length);

        return hd.raw_data;
    }
}


/* Global variables */
var g_inputs;

function fill_image_header_date_time() {

    if (verbose) WScript.Echo(new Date());
    objTimeStamp = new TimeStamp();
    objTimeStamp.fill_repeat_current_date_to_byte_array(image_header, 45, 2);

    // Always run correct    
    return new Array(0, "OK");
}

function parsing_and_checking_input_arguments(image_header) {
    // Input named arguments layout
    //  linker: Linker path
    //  platform: Platform name (max 32 bytes, the extra will be strip off)
    //  version: Initial version (3 byte hexa)
    //  device_size: MCU device ROM size (linear) (hexa)
    //  setting_bootloader: Setting of bootloader: AbsPath/StrHexAddressRange
    //  setting_user: Setting of user application: AbsPath/StrHexAddressRange
    //  setting_metrology: Setting of fixed metrology: AbsPath/StrHexAddressRange
    //  verbose: (enable more debug print for the code) (if not defined means false)

    // Sample (for debug): 
    //      cscript temp.js //nologo /linker:"C:\bin\rlink.exe" /platform:"1P2W_I1C512K_SM" /version:0x000001 /device:0x80000 /setting_bootloader:"C:\bootloader.abs"/00000-02fff /setting_user:"C:\rl78i1c.abs"/03000-36bff /setting_metrology:"C:\em_middleware.abs"/37c00-3ffff
    // Note: Extreme path  "C:\ProgramFiles (x86)\Renesas Electronics\CS+_-=[];',.ab & cd~`42/2958-203812"
    try
    {
        var args = WScript.Arguments.Named;

        verbose = 0;
        for (var i = 0 ; i < WScript.Arguments.length; i++)
        {
            if (WScript.Arguments.Item(i) == "/verbose")
            {
                verbose = 1;
                break;
            }
        }

        if (verbose) WScript.Echo("Parsing input arguments")
        g_inputs = new InputArgs(image_header);
        g_inputs.Parse(
            args.Item("linker"),
            args.Item("user_clnk"),
            args.Item("header"),
            args.Item("image"),
            args.Item("transfer"),
            args.Item("production"),
            args.Item("platform"),
            args.Item("version"),
            args.Item("device"),
            args.Item("setting_bootloader"),
            args.Item("setting_user"),
            args.Item("setting_metrology"),
            image_header
        );

    
        // Print debug information
        if (verbose)
        {
            WScript.Echo("Number of arguments: " + args.length);

            WScript.Echo("Linker path: " + g_inputs.LinkerPath);
            WScript.Echo("Identifier: " + g_inputs.ImageIdentifierStr);
            WScript.Echo("User clnk path: " + g_inputs.UserAppLinkerOptionFilePath);
            WScript.Echo("Generate image header path: " + g_inputs.ImageHeaderFilePath);
            WScript.Echo("Generate image folder path: " + g_inputs.ImageFolderPath);
            WScript.Echo("Transfer image file path: " + g_inputs.TransferImageFilePath);
            WScript.Echo("Production image file path: " + g_inputs.ProductionImageFilePath);
            WScript.Echo("DeviceSize (Integer, string): " + g_inputs.IntDeviceSize + " " + g_inputs.StrDeviceSize);
            WScript.Echo("Parsed user app setting: " + g_inputs.UserAppInfo.AbsPath, g_inputs.UserAppInfo.StrHexAddressRange);
            WScript.Echo("Calculated user app code with header hex range: " + g_inputs.UserAppInfo.StrHexAddressRangeWithHeader);
            WScript.Echo("Calculated user app code with header size: " + g_inputs.UserAppInfo.IntCodeSizeWithHeader + "-0x" + g_inputs.UserAppInfo.IntCodeSizeWithHeader.toString("16") + "(bytes)");
            WScript.Echo("Calculated user app code no header hex range: " + g_inputs.UserAppInfo.StrHexAddressRangeNoHeader);
            WScript.Echo("Calculated user app code no header size: " + g_inputs.UserAppInfo.IntCodeSizeNoHeader + "-0x" + g_inputs.UserAppInfo.IntCodeSizeNoHeader.toString("16") + "(bytes)");
            WScript.Echo("Is bootloader used: " + g_inputs.BootloaderInfo.Used);
            if (g_inputs.BootloaderInfo.Used) {
                WScript.Echo("Parsed bootloader setting: " + g_inputs.BootloaderInfo.AbsPath, g_inputs.BootloaderInfo.StrHexAddressRange);
            }
            WScript.Echo("Is fixed metrology used: " + g_inputs.FixedMetrologyInfo.Used);
            if (g_inputs.FixedMetrologyInfo.Used) {
                WScript.Echo("Parsed fixed metrology setting: " + g_inputs.FixedMetrologyInfo.AbsPath, g_inputs.FixedMetrologyInfo.StrHexAddressRange);
            }

            //Print address information
            WScript.Echo("Address range, ShiftStartAddress");
            WScript.Echo("UserApp: " + g_inputs.UserAppInfo.StrHexAddressRange, g_inputs.UserAppInfo.StrShiftStartAddress);
            WScript.Echo("Bootloader: " + g_inputs.BootloaderInfo.StrHexAddressRange, g_inputs.BootloaderInfo.StrShiftStartAddress);
            WScript.Echo("FixedMetrology: " + g_inputs.FixedMetrologyInfo.StrHexAddressRange, g_inputs.FixedMetrologyInfo.StrShiftStartAddress);

            //Print path information
            WScript.Echo("UserAppMotFile: " + g_inputs.UserAppInfo.MotFilePathCurrentbank, g_inputs.UserAppInfo.MotFilePathRewritebank);
            WScript.Echo("BootloaderMotFile: " + g_inputs.BootloaderInfo.MotFilePathCurrentbank, g_inputs.BootloaderInfo.MotFilePathRewritebank);
            WScript.Echo("FixedMetrologyMotFile: " + g_inputs.FixedMetrologyInfo.MotFilePathCurrentbank, g_inputs.FixedMetrologyInfo.MotFilePathRewritebank);

        }
    }
    catch (e)
    {
        // Error code, description
        throw new Error(5, e.description);
    }

    return new Array(0, "OK");
}

function generate_image_header_fields(image_header) {
    try
    {
        var objCCRL = new CCRL_Helper();
        var result;

        if (verbose) WScript.Echo(" |--- Generating identifier and software version field");
        image_header.SetIdentifier(g_inputs.ImageIdentifierStr);
        image_header.SetSoftwareVersion(g_inputs.ImageSoftwareVersionValue);

        if (verbose) WScript.Echo(" |--- Generating user application size field");
        image_header.SetUserAppSize(g_inputs.UserAppInfo.IntCodeSizeWithHeader);
        if  (verbose) WScript.Echo("UserAppSize: " + g_inputs.UserAppInfo.IntCodeSizeWithHeader + "-0x" + g_inputs.UserAppInfo.IntCodeSizeWithHeader.toString("16") + " (bytes)");
        if  (verbose) WScript.Echo("UserAppSize Without Header : " + (image_header.GetUserAppSize())  + "-0x" + image_header.GetUserAppSize().toString("16") + " (bytes)");
        
        if (verbose) WScript.Echo(" |--- Generating hash fields: user application");
        result = objCCRL.calculate_crc_from_abs_file(g_inputs.LinkerPath, g_inputs.UserAppInfo.AbsPath, g_inputs.UserAppInfo.StrHexAddressRangeNoHeader);
        if  (verbose) WScript.Echo("UserApp CRC: " + result.crc_string);
        image_header.SetUserAppHash(result.crc_value);

        if (verbose) WScript.Echo(" |--- Generating transfer and activate time fields");
        var dt = new Date();
        result = image_header.SetTransferDateTime(dt);
        result = image_header.SetActivateDateTime(dt);
        if  (verbose) WScript.Echo("Current string date time: " + dt);
        if  (verbose) WScript.Echo("Current byte aray date time: " + result);
    }
    catch (e)
    {
        // Error code, description
        throw new Error(5, e.description);
    }
}

function creating_image_header_file(image_header) {
    try
    {
        outfile = g_inputs.ImageHeaderFilePath;
        if (verbose) WScript.Echo(" |--- Exporting image header to file: " + outfile);
        Lib.binArrayToFile(image_header.GetImageHeader(), outfile);
    }
    catch (e)
    {
        // Error code, description
        throw new Error(5, e.description);
    }
}

function linking_generated_header_file(image_header) {
    try
    {
        var objCCRL = new CCRL_Helper();
        if (verbose) WScript.Echo(" |--- Call linker again to link generated header file to user application abs file: ");
        objCCRL.link_with_clnk_file(g_inputs.LinkerPath, g_inputs.UserAppLinkerOptionFilePath);
    }
    catch (e)
    {
        // Error code, description
        throw new Error(5, e.description);
    }
}

function creating_production_mot_file(image_header) {
    try
    {
        var objCCRL = new CCRL_Helper();
        
        if (verbose) WScript.Echo(" |--- Generating user application mot file: both banks ");
        objCCRL.output_mot_file_from_abs(g_inputs.LinkerPath, g_inputs.UserAppInfo.AbsPath, g_inputs.UserAppInfo.MotFilePathCurrentbank, g_inputs.UserAppInfo.StrHexAddressRange, null);
        objCCRL.output_mot_file_from_abs(g_inputs.LinkerPath, g_inputs.UserAppInfo.AbsPath, g_inputs.UserAppInfo.MotFilePathRewritebank, g_inputs.UserAppInfo.StrHexAddressRange, g_inputs.UserAppInfo.StrShiftStartAddress);

        if (verbose) WScript.Echo(" |--- Generating bootloader mot file: both banks ");
        objCCRL.output_mot_file_from_abs(g_inputs.LinkerPath, g_inputs.BootloaderInfo.AbsPath, g_inputs.BootloaderInfo.MotFilePathCurrentbank, g_inputs.BootloaderInfo.StrHexAddressRange, null);
        objCCRL.output_mot_file_from_abs(g_inputs.LinkerPath, g_inputs.BootloaderInfo.AbsPath, g_inputs.BootloaderInfo.MotFilePathRewritebank, g_inputs.BootloaderInfo.StrHexAddressRange, g_inputs.BootloaderInfo.StrShiftStartAddress);

        if (g_inputs.FixedMetrologyInfo.Used == true)
        {
            if (verbose) WScript.Echo(" |--- Generating fixed metrology mot file: both banks ");
            objCCRL.output_mot_file_from_abs(g_inputs.LinkerPath, g_inputs.FixedMetrologyInfo.AbsPath, g_inputs.FixedMetrologyInfo.MotFilePathCurrentbank, g_inputs.FixedMetrologyInfo.StrHexAddressRange, null);
            objCCRL.output_mot_file_from_abs(g_inputs.LinkerPath, g_inputs.FixedMetrologyInfo.AbsPath, g_inputs.FixedMetrologyInfo.MotFilePathRewritebank, g_inputs.FixedMetrologyInfo.StrHexAddressRange, g_inputs.FixedMetrologyInfo.StrShiftStartAddress);
        }

        
        if (verbose) WScript.Echo(" |--- Generating each bank production mot file ");
        if (g_inputs.FixedMetrologyInfo.Used == true)
        {
            objCCRL.concatenate_mot_file(g_inputs.LinkerPath, g_inputs.ProductionImageFilePathCurrentbank, new Array(g_inputs.UserAppInfo.MotFilePathCurrentbank, g_inputs.FixedMetrologyInfo.MotFilePathCurrentbank, g_inputs.BootloaderInfo.MotFilePathCurrentbank));
            objCCRL.concatenate_mot_file(g_inputs.LinkerPath, g_inputs.ProductionImageFilePathRewritebank, new Array(g_inputs.UserAppInfo.MotFilePathRewritebank, g_inputs.FixedMetrologyInfo.MotFilePathRewritebank, g_inputs.BootloaderInfo.MotFilePathRewritebank));
        } else {
            objCCRL.concatenate_mot_file(g_inputs.LinkerPath, g_inputs.ProductionImageFilePathCurrentbank, new Array(g_inputs.UserAppInfo.MotFilePathCurrentbank, g_inputs.BootloaderInfo.MotFilePathCurrentbank));
            objCCRL.concatenate_mot_file(g_inputs.LinkerPath, g_inputs.ProductionImageFilePathRewritebank, new Array(g_inputs.UserAppInfo.MotFilePathRewritebank, g_inputs.BootloaderInfo.MotFilePathRewritebank));
        }

        if (verbose) WScript.Echo(" |--- Generating final whole device production mot file ");
        objCCRL.concatenate_mot_file(g_inputs.LinkerPath, g_inputs.ProductionImageFilePath, new Array(g_inputs.ProductionImageFilePathCurrentbank, g_inputs.ProductionImageFilePathRewritebank));
    }
    catch (e)
    {
        // Error code, description
        throw new Error(5, e.description);
    }
}

function creating_transfer_image_file(image_header) {
    try
    {
        var objCCRL = new CCRL_Helper();

        if (verbose) WScript.Echo(" |--- Generating user aplication binary transfer image (include image header) ");
        objCCRL.output_binary_file_from_abs(g_inputs.LinkerPath, g_inputs.UserAppInfo.AbsPath, g_inputs.TransferImageFilePath, g_inputs.UserAppInfo.StrHexAddressRangeWithHeader, null);

        if (verbose) WScript.Echo(" |--- Read image file and replace with transfer image header");
        var transfer_file = new Array();
        Lib.binFileToArray(g_inputs.TransferImageFilePath, transfer_file);

        var transfer_header = image_header.GetTransferImageHeader();
        Array.prototype.splice.apply(transfer_file, [0, transfer_header.length].concat(transfer_header));

        if (verbose) WScript.Echo(" |--- Write back to make final transfer image header");
        Lib.binArrayToFile(transfer_file, g_inputs.TransferImageFilePath);
    }
    catch (e)
    {
        // Error code, description
        throw new Error(5, e.description);
    }
}

function wscriptMain() {
    try {
        var image_header = new ImageHeader();
        
        WScript.Echo("WScript JScript environment version: " + WScript.Version);

        WScript.Echo("--- Parsing and checking input arguments");
        status = parsing_and_checking_input_arguments(image_header);
    
        WScript.Echo("--- Generating image header fields");
        status = generate_image_header_fields(image_header);
    
        WScript.Echo("--- Creating image header file");
        status = creating_image_header_file(image_header);
    
        WScript.Echo("--- Linking generated image header file on user application ");
        status = linking_generated_header_file(image_header);
    
        WScript.Echo("--- Creating production mot file");
        status = creating_production_mot_file(image_header);
        
        WScript.Echo("--- Creating transfer image file");
        status = creating_transfer_image_file(image_header);

        WScript.Quit(0);
    }
    catch (e) {
        // Error code, description
        WScript.Echo(e.description);
        WScript.Quit(5);
    }
}
  
//Execution point
wscriptMain();