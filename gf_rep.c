#include <stdio.h>
#include <string.h>

#define GF_FIELD        16

#if(16 > GF_FIELD)
#define DATA_TYPE		 long
#else
#define DATA_TYPE		 int
#endif

#define LARGER		     1
#define SMALLER		     0

unsigned DATA_TYPE prim_polynomial = 0x13;

unsigned DATA_TYPE get_ld(unsigned DATA_TYPE poly)
{
	unsigned DATA_TYPE i = 0;
	unsigned DATA_TYPE ld = 0;

	for(i = 0; i < 16; i++)
	{
		if((1 << i) > poly)
		{
			ld = i - 1;
			break;
		}
	}
	//printf("ld: %x\n", ld);

	return ld;
}

unsigned DATA_TYPE get_lt(unsigned DATA_TYPE poly)
{
	unsigned DATA_TYPE lt = 0;

	lt = 1 << (get_ld(poly));

	//printf("lt: %x\n", lt);

	return lt;
}

unsigned DATA_TYPE check_poly(unsigned DATA_TYPE poly)
{
	unsigned DATA_TYPE ld = get_ld(prim_polynomial);
	//if((1 << 4) == poly)printf("check_poly: %x %d\n", ld, get_ld(poly));
	if(ld <= get_ld(poly))
	{
		return LARGER;
	}
	else
	{
		return SMALLER;
	}
}

unsigned DATA_TYPE decompose_term(unsigned DATA_TYPE term_degree)
{
	unsigned DATA_TYPE down_poly = 0, lt_poly = 0;
	unsigned DATA_TYPE term_left = 0;
	unsigned DATA_TYPE ld = get_ld(prim_polynomial);
	
	if(ld > term_degree)
	{
		down_poly = term_degree;
	}
	else
	{
		lt_poly = prim_polynomial ^ (1 << ld);
		term_left = term_degree - ld;
		down_poly = lt_poly << term_left;
		//printf("down_poly: %x %x %x %d %d\n", down_poly, lt_poly, term_left, ld, prim_polynomial);
	}
	
	return down_poly;
}

unsigned DATA_TYPE main()
{
	unsigned DATA_TYPE i = 0;
	unsigned DATA_TYPE input_poly = 0, output_poly = 0xFF;
	unsigned DATA_TYPE ld = 0, lt = 0;
	unsigned DATA_TYPE tmp_term= 0, left_term = 0;

	for(i = 0; i < (GF_FIELD - 1); i++)
	{
		input_poly = 1 << i;
		output_poly = input_poly;

		while(LARGER == check_poly(output_poly))
		{
			//if(i == 4)printf("cal_poly: %x\n", output_poly);
			ld = get_ld(output_poly);
			//if(i == 4)printf("ld: %x\n", ld);
			lt = get_lt(output_poly);
			//if(i == 4)printf("lt: %x\n", lt);
			tmp_term = decompose_term(ld);
			left_term = output_poly ^ lt;

			output_poly = left_term ^ tmp_term;
			//if(i == 4)printf("output_poly: %x %x %x\n", output_poly, left_term, tmp_term);
		}
		printf("poly: %x %x\n", i, output_poly);
	}
	
	return 0;
}
