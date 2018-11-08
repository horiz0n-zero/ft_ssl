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

     -e                  Encode (default)
    
     -d                  Decode incoming Base64 stream into binary data.
     
     -i input_file       Read input from input_file.  Default is stdin; passing - also represents stdin.

     -o output_file      Write output to output_file.  Default is stdout; passing - also represents stdout.

ft_ssl des|des-ecb|des-cbc [-dea] [-i input file] [-o output file] [-k key] [-p password] [-s salt] [v vector IV]

	-a					Decode/encode the input/output in base64, depending on the encrypt mode

	-d					Decrypt mode

	-e					Encrypt mode (default)

	-i input_file		Read input from input_file.  Default is stdin; passing - also represents stdin.

	-o output_file		Write output to output_file.  Default is stdout; passing - also represents stdout.

	-k key				Key in hexa

	-p password			Password in ascii

	-s salt				Salt in hexa

	-v vector			Initialization vector in hexa
