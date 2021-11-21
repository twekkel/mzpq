# mzpq

mzpq compresses files using the ZPAQ compression library. The  command-line options are deliberately very similar to those of gzip/bzip2/xz/zstd, but they are not identical. In general mzpq will achive very high compression, at the cost of memory and speed.

zpaq is a journaling archiver written by Matt Mahoney. The command line for zpaq is suited for creating encrypted, deduplicated, compressed, incremental archives and backups. mzpq uses the same compression library, but with a simpler command line interface for compression only. zpaq can still extract compressed files created by mzpq.

'm' in mzpq means micro/mini/minimalistic/... 'a' has been stripped off, as it is not an archiver like zpaq.

Currently file attributes are not preserved.

No Warranty. Use at your own risk. Make backups.


### Installing

Build:
```
make
```

Install:
```
sudo make install
```


**Examples usage**

Help:
```
mzpq -h
```

Compress a file:
```
mzpq -7 syslog.log
```

Use advanced compression method, see libzpaq.h for details:
```
mzpq -mx6.3ci1 *.log
```

Read from standard in, compress and redirect to a compressed file:
```
cat syslog.log | mzpq -3c > syslog.log.zpq
```


## Benchmark

Compressing enwik8, the first 10<sup>8</sup> bytes of the English Wikipedia dump on Mar. 3, 2006.

All compressors were used with the default compression level.

| Compressor    | comp size (bytes) | comp time (s) | decomp time (s) |
|:--------------|------------------:|--------------:|----------------:|
| -             |        1000000000 |             - |               - |
| lz4 -1        |          57285984 |          0.35 |            0.13 |
| gzip -6       |          36518329 |          4.73 |            0.71 |
| zstd -3       |          35626935 |          0.72 |            0.22 |
| bzip2 -9      |          29008758 |          7.59 |            3.45 |
| xz -6         |          26375764 |         65.59 |            1.51 |
| PPMd -m10 -o4 |          26275353 |          6.52 |            7.11 |
| **mzpq -4**   |          21979813 |         85.01 |           87.66 |
| **mzpq -9**   |          19136943 |        254.64 |          268.73 |

Note: '-4' is the default compression level for mzpq, '-9' is the maximum.


## License

mzpq is released to the public domain.

zpaq is written by Matt Mahoney and released to the public domain. It includes code from libdivsufsort 2.0 (C) Yuta Mori, 2003-2008, MIT license, public domain code for AES from libtomcrypt by Tom St Denis and public domain code for salsa20 by D. J. Bernstein. 


## Acknowledgments

* http://mattmahoney.net/dc/zpaq.html
