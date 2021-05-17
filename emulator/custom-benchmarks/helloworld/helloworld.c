#include "util.h"

#define DATA_SIZE 20

int input_data1[DATA_SIZE] = 
{
	267, 952, 229, 800, 337, 584, 944, 643, 902, 368, 241, 489, 913, 328, 826, 313, 933, 592, 985, 388
};

int input_data2[DATA_SIZE] = 
{
	584, 989,  62, 271, 985, 853, 403, 788, 346, 531, 517, 222, 559, 461, 908, 241, 775, 358, 255, 332
};

int verify_data[DATA_SIZE] = 
{
  155928, 941528, 14198, 216800, 331945, 498152, 380432, 506684, 312092, 195408, 124597, 108558, 510367, 151208, 750008, 75433, 723075, 211936, 251175, 128816
};


int multiply( int x, int y )
{
	int i;
	int result = 0;

	for (i = 0; i < 32; i++) {
		if ((x & 0x1) == 1)
			result = result + y;
		x = x >> 1;
		y = y << 1;
	} 
	return result;
}


int main( int argc, char* argv[] )
{
	int i;
	int results_data[DATA_SIZE];

#if PREALLOCATE
	for (i = 0; i < DATA_SIZE; i++)
	{
		results_data[i] = multiply( input_data1[i], input_data2[i] );
	}
#endif

	setStats(1);
	for (i = 0; i < DATA_SIZE; i++)
	{
		results_data[i] = multiply( input_data1[i], input_data2[i] );
	}
	setStats(0);

	// Check the results
	return verify( DATA_SIZE, results_data, verify_data );

}
