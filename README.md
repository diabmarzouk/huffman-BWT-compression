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
