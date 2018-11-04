# ft_ssl
cryptographic hashing algorithms [md5 sha256]

*Usage*
ft_ssl md5|sha256 [-pqr] [-s string] [file ...]
     -s string
             Print a checksum of the given string.

     -p      Echo stdin to stdout and append the checksum to stdout.

     -q      Quiet mode - only the checksum is printed out.  Overrides the -r option.

     -r      Reverses the format of the output.  This helps with visual diffs.  Does nothing when combined with the -ptx options.
