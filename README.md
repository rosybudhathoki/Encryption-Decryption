Use the following command in the current directory. ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>

YOU CAN USE make to access the encrypt.c file after that use: ./encrypt -t mapping_encryption.csv -m 1 -i input_encryption.txt --> for encryption. The order doesn't matter unless and until you have the right flag before file name.

./encrypt -t mapping_decryption.csv -m 2 -i input_decryption.txt --> for decryption. The order doesn't matter unless and until you have the right flag before file name.
  
  This code was written by me for one of my programming Methodology class.
