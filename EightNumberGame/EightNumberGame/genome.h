#ifndef GENOME_H
#define GENOME_H

#include <vector>

#define GENOME_LEN 2

using namespace std;

class Genome
{
public:
	Genome(int geneLen);

	int bit[GENOME_LEN];
};

#endif