#include "libzpaq.h"
#include <unistd.h>
#include <string>

const std::string suffix = ".zpq";


void libzpaq::error(const char* msg) {
	fprintf(stderr, "Oops: %s\n", msg);
	exit(1);
}

class In: public libzpaq::Reader {
public:
	int get() {return getchar();}
} in;

class Out: public libzpaq::Writer {
public:
	void put(int c) {putchar(c);}
} out;

bool fexists(const std::string file) {
	return( access( file.c_str(), F_OK ) != -1 );
}

void usage() {
	printf(
"Usage: mzpq [-1..9] [-cdfhV] [-m method] [files]\n"
"\n"
" -1..9 compression level, default 4\n"
" -c    write to standard output\n"
" -d    decompress\n"
" -f    force overwrite of output file\n"
" -h    this help\n"
" -m    compression method, see libzpaq.h for details\n"
" -V    version\n"
	);
	exit(1);
}

void version() {
	printf("mzpq 0.1\n");
	printf("libzpaq 7.15\n");
	exit(0);
}

int main(int argc, char **argv) {

	int c = 0;
	bool conout   = false;
	bool compress = true;
	bool force    = false;
	std::size_t found;
	std::string method = "4";
	std::string fname;
	std::string fnorg;

	// Parse command line arguments
	while ((c = getopt (argc, argv, "123456789cdfhm:V")) != -1)
	switch(c)
	{
	case '1':
		method = "1";
		break;
	case '2':
		method = "2";
		break;
	case '3':
		method = "3";
		break;
	case '4':
		method = "4";
		break;
	case '5':
		method = "47";
		break;
	case '6':
		method = "51";
		break;
	case '7':
		method = "54";
		break;
	case '8':
		method = "57";
		break;
	case '9':
		method = "59";
		break;
	case 'c':
		conout = true;
		break;
	case 'd':
		compress = false;
		break;
	case 'f':
		force = true;
		break;
	case 'h':
		usage();
		break;
	case 'm':
		method = optarg;
		break;
	case 'V':
		version();
		break;
	default:
		usage();
	}

	// Loop over the file names
	for ( int i = optind; i < argc; i++ ) {

		if ( argv[i] != NULL ) fname = argv[i];
		if ( fname.compare("-") == 0) fname.clear();
		std::string fnorg = fname;

		// Try to read from file
		if ( ! fname.empty() && ! fexists(fname) ) {
			fprintf(stderr, "%s does not exists\n", fname.c_str());
			exit(1);
		}

		if ( ! fname.empty() ) {
			stdin = freopen( fname.c_str() , "r", stdin );
		}

		// Compress
		if ( compress && ! conout && ! fname.empty() ) {
			fname += suffix;
			if ( ! force && fexists(fname) ) {
				fprintf(stderr, "%s already exists\n", fname.c_str());
				return 1;
			}
			stdout = freopen(fname.c_str() , "w", stdout);
		}

		// Decompress
		if ( ! compress && ! conout && ! fname.empty() ) {
			found = fname.find(suffix);
			if ( found == std::string::npos ) {
				fprintf(stderr, "unknown suffix: %s\n", fname.c_str());
				exit(1);
			}
			fname = fname.substr( 0, found );
			if ( ! force && fexists(fname) ) {
				fprintf(stderr, "%s already exists\n", fname.c_str());
				return 1;
			}
			stdout = freopen(fname.c_str() , "w", stdout);
		}

		// Do the actual work
		if ( compress ) {
			libzpaq::compress(&in, &out, method.c_str(), fnorg.c_str());
		} else {
			libzpaq::decompress(&in, &out);
		}
	}

	// Flush output streams before exiting
	fflush(stdout);
}
