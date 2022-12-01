// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER
#include "../hdrs/common.hpp"

int main( int argc, char* argv[] )
{

	srand (time(NULL));
	int result = Catch::Session().run( argc, argv );

	return ( result < 0xff ? result : 0xff );
}
