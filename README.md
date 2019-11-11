# mzpq

mzpq compresses files using the ZPAQ compression library. The  command-line options are deliberately very similar to those of gzip/bzip2/xz/zstd, but they are not identical. In general mzpq will achive very high compression, at the cost of memory and speed.

zpaq is a journaling archiver written by Matt Mahoney. The command line for zpaq is suited for creating compressed, incremental backups. mzpq uses the same compression library, but a different command line interface. zpaq can still extract compressed files created by mzpq.

'm' in mzpq stands for micro/mini/minimalistic/... 'a' has been stripped of, as it is not an archiver like zpaq.

Currently file attributes are not preserved.

No Warranty. Use at your own risk. Make backups.

### Installing

Build:
```
make
```

Install:
```
make install
```

**Examples usage**

Help:
```
mzpq -h
```

Compress a file:
```
mzpq -3 syslog.log
```

Decompress a file to standard out and look for ERROR:
```
mzpq -dc syslog.log.zpq | grep ERROR
```

Read from standard in, compress and redirect to a compressed file:
```
cat syslog.log | mzpq -3c > syslog.log.zpq
```

## License

mzpq is released to the public domain.

zpaq is written by Matt Mahoney and released to the public domain. It includes code from libdivsufsort 2.0 (C) Yuta Mori, 2003-2008, MIT license, public domain code for AES from libtomcrypt by Tom St Denis and public domain code for salsa20 by D. J. Bernstein. 

## Acknowledgments

* http://mattmahoney.net/dc/zpaq.html
