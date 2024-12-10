# Move-To-Front (MTF)-Transform

MTF transform is typically used to improve entropy encoding for compression. Keep in mind that it is not a compression algorithm itself; rather a pre-processor step for compression itself. Depending on the characteristics of the data, benefits achieved by this step greatly justify this additional step.

This algorithm was first published by Boris Ryabko under the name of "book stack" in 1980.
  
This algorithm greatly benfits frequently occuring literals. This greatly benefits the actual compression stage (eg. DEFLATE). A typical algorithm like Huffman Encoding would see higher number of frequency counts as a result of MTF Transform, eventually resulting in greater (better) compression ratios.

MTF transform is shown in the example below:
For simplicity we will assume that encoding values are from a-to-z only (instead of ASCII 0-255).

## Example: "hellohelloooo"

| Iteration | Sequence | List |
| --- | --- | --- |
| **h**ellohelloooo | 7 | (abcdefghijklmnopqrstuvwxyz) |
| h**e**llohelloooo | 7,5 | (habcdefgijklmnopqrstuvwxyz) |
| he**l**lohelloooo | 7,5,11 | (ehabcdfgijklmnopqrstuvwxyz) |
| hel**l**ohelloooo | 7,5,11,0 | (lehabcdfgijkmnopqrstuvwxyz) |
| hell**o**helloooo | 7,5,11,0,14 | (lehabcdfgijkmnopqrstuvwxyz) |
| hello**h**elloooo | 7,5,11,0,14,3 | (olehabcdfgijkmnpqrstuvwxyz) |
| helloh**e**lloooo | 7,5,11,0,14,3,3 | (holeabcdfgijkmnpqrstuvwxyz) |
| hellohe**l**loooo | 7,5,11,0,14,3,3,3 | (eholabcdfgijkmnpqrstuvwxyz) |
| hellohel**l**oooo | 7,5,11,0,14,3,3,3,0 | (lehoabcdfgijkmnpqrstuvwxyz) |
| hellohell**o**ooo | 7,5,11,0,14,3,3,3,0,0 | (lehoabcdfgijkmnpqrstuvwxyz) |
| hellohello**o**oo | 7,5,11,0,14,3,3,3,0,0,3 | (olehabcdfgijkmnpqrstuvwxyz) |
| hellohelloo**o**o | 7,5,11,0,14,3,3,3,0,0,3,0 | (olehabcdfgijkmnpqrstuvwxyz) |
| hellohellooo**o** | 7,5,11,0,14,3,3,3,0,0,3,0,0 | (olehabcdfgijkmnpqrstuvwxyz) |
| Final String | 7,5,11,0,14,3,3,3,0,0,3,0,0 | (olehabcdfgijkmnpqrstuvwxyz) |



