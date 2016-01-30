#ifndef GENOME_H
#define GENOME_H

#include <vector>

using namespace std;

class Genome
{
public:
	Genome(int len);
private:
	vector<int> bits;
};

#endif