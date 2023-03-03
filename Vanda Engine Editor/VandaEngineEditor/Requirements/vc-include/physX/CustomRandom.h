// based on The Open Group Base Specifications Issue 6

class Random
{
	unsigned long next;

public:

	static const unsigned int rand_max = 32767;

	Random(unsigned seed = 1)
	{
		next = 0;
		srand(seed);
	}

	int rand(void)  /* RAND_MAX assumed to be 32767. */
	{
	    next = next * 1103515245 + 12345;
	    return((unsigned)(next/65536) % 32768);
	}

	void srand(unsigned seed)
	{
	    next = seed;
	}
};
