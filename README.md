# ft_ssl
cryptographic hashing algorithms [md5 sha256]

*Usage*

ft_ssl md5|sha256 [-pqr] [-s string] [file ...]
     -s string
             Print a checksum of the given string.

     -p      Echo stdin to stdout and append the checksum to stdout.

     -q      Quiet mode - only the checksum is printed out.  Overrides the -r option.

     -r      Reverses the format of the output.  This helps with visual diffs.  Does nothing when combined with the -ptx options.

ft_ssl base64 [-de] [-i input file] [-o output file]

     -e                  encode (default)
    
     -d                  Decode incoming Base64 stream into binary data.
     
     -i input_file       Read input from input_file.  Default is stdin; passing - also represents stdin.

     -o output_file      Write output to output_file.  Default is stdout; passing - also represents stdout.
