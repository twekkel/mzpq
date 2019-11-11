# mzpq

mzpq compresses files using the ZPAQ compression library. The  command-line options are deliberately very similar to those of gzip/bzip2/xz/zstd, but they are not identical.

zpaq is a journaling archiver written by Matt Mahoney. The command line for zpaq is suited for creating compressed, incremental backups. mzpq uses the same compression library, but a different command line interface. zpaq can extract compressed files created by mzpq.

'm' in mzpq stands for micro/mini/minimalistic/... 'a' has been stripped of, as it is not an archiver like zpaq.

No Warranty. Use at your own risk. Make backups.

### Installing

Buid:
```
make
```

Install:
```
make install
```

Examples:
Compress a file:
```
mzpq -3 fp.log
```

Decompress to standard out:
```
mzpq -dc fp.log.zpq
```

Compress from standard in:
```
cat fp.log | mzpq -3c > fp.log.zpq
```

## License

mzpq is released to the public domain.

zpaq is written by Matt Mahoney and released to the public domain. It includes code from libdivsufsort 2.0 (C) Yuta Mori, 2003-2008, MIT license, public domain code for AES from libtomcrypt by Tom St Denis and public domain code for salsa20 by D. J. Bernstein. 

## Acknowledgments

* http://mattmahoney.net/dc/zpaq.html
