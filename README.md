# Huffman-Burrow Wheelers Transformation Compression
Motivation
The motivation for creating this project lies behind for my peeked interest in compression and its optimization methods. Compared to other subjects presented in Multimedia, compression was one of the more ‘magical’ ones that stood out to me. I was told about Burrow Wheelers Transformation in one of my undergraduate classes. I remember hearing that Huffman benefits from strings that tend to be consistent in the same characters when back-to-back from each other (e.g. “AAAAABBBBBCCCC”). That is when I knew that Burrows-Wheeler Transform could potentially help optimize Huffman encoding.

This project has only been tested on UNIX based systems such as Linux & macOS. Furthermore, it has only been tested to compress text files, however, it theoretically should be able to compress all sorts of files.

To compile this project on Linux/macOS, run the Makefile command:
**Make main**

This will compile all headers and the main.cpp.

To remove all files run:
**Make clean**

To debug:
**Make debug**

## Instruction
There are two programs in my project. One for Burrows-Wheeler Transform + Huffman, and another for Huffman itself. I compiled these programs in Ubuntu 18.04. To run them use these commands in the CLI.
./bwtHuff “mode” “input file” “output file” (Modes: -c (compression), -d (decompression), -bwt(to test bwt itself; it will take a string, transform it, and inverse the transformation)).
./huff “mode” “input file” “output file” (Modes: -c (compression), -d (decompression))
  
The input file should be any file that contains ASCII characters (not including STX or ETX). The output file will be created in the program, so you can type any name you want and it will make it for you. When you go to decompress, make sure to use your output file from the compression otherwise you will get an invalid input. The decompression output will append .bwtHuff to the file name (only in bwtHuff program).


## Problem
Huffman encoding is a lossless comrpession algorithm. With that, we know that the compression may not be the smallest compression, but at least we will contain every piece of data we first had. The project needed two main components to be complete. It needed Burrows-Wheeler Transform(and its inverse for decoding), and Huffman compression. The main problem faced while creating this program was attempting to combine both Burrows-Wheeler Transform and Huffman encoding into one program.

## Solution
A small overview for what Burrows-Wheeler Transform is; it is a text transformation algorithm that is reversible, whereas the string can not contain the ASCII characters STX (Hex: 0x02) or ETX(Hex: 0x03). These two characters are vital for the transformation to work correctly. To begin, you prepend STX and append ETX to the original string you want to transform. Once that is done, you create a vector of strings with the size of the original string + 2. From here, you rotate the string string.size() times to the right. So “^BANANA|” would become “|^BANANA”, and you keep doing this until you have rotated the whole string as a whole and push each string to the vector. You then use a sorting algorithm to sort the vector. After that, you make a new string that contains the last character of each string in the vector from 0 -> vector.size() - 1. This ‘column vector’ string will always do its best at grouping similar characters in the string together. This string is the transformed string. Its inverse has a similar process, you get the transformed string and create a column vector containing one of each character from the string. You then sort after appending the characters and then continue to prepend the transformed string and sort every time you prepend the transformed string. Doing this will
    
recreate the original un-transformed string; all you have to do is look in the vector for the string that ends with ETX and you have your original string. Huffman encoding probably does not an overview, but it builds a binary tree containing the frequencies, positions, and compresses the original data using that knowledge. In the end, I wanted to see if compressing data that has been transformed will provide a better compression whereas if the data was not transformed. As mentioned in the Problem section, I implemented Burrows-Wheeler Transform, Inverse Burrows-Wheeler Transform, and the Huffman codec. My solution to this was to create each part individually and test as I go to make sure it all works, and once it is all done, I created a codec file that will handle both the Burrows-Wheeler Transformations and Huffman compression. In short, to compress, I would first take the input and then transform each word one by one and and then pass through the completed new transformed string and compressed the whole file as a string. To decompress, I would first need to decompress the files contents, which then gives me the transformed text, I take this and perform the inverse BWT to recieve the original text.

## Evaluation
To evaluate my hypothesis of Burrows-Wheeler Transform optimizing Huffman encoding;
well it didn’t, kind of. When using pure huffman compression on a Shrek Movie text script (which is included under src), I recieved a compression of 54354 bytes -> 32798 bytes. Whereas compared to my program of Burrows-Wheeler Transform and Huffman combined, I recieved a compression of 61216 bytes -> 37484 bytes. Looking at this data, it is clear that having to add STX and ETX to each string that needed to be transformed added up quite a bit, but the compression was more or less the same. The difference of the pure huffman compression was 21556 bytes, where as the other one was 23732 bytes. As you can see, they are quite similar and not far off. But nevertheless, the BWT+Huffman program did add about 7000 bytes to the file, making it quite unoptimized. I personally believe that my program could optimize better if I changed the methods of transforming the strings.
