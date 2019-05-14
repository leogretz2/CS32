#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

class GenomeMatcherImpl
{
public:
	GenomeMatcherImpl(int minSearchLength);
	void addGenome(const Genome& genome);
	int minimumSearchLength() const;
	bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
	bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
	struct segValue {
		segValue(int position, string name) : m_pos(position), m_name(name) {}
		int m_pos;
		string m_name;
	};
	int m_minSearch;
	vector<Genome> gvec;
	Trie<segValue> gtrie;	
	DNAMatch createDNA(string name, int length, int position) const;
	GenomeMatch createGenomeMatch(string name, int matches, int totalNum) const;
	bool containsGenome(vector<DNAMatch> matches, string name, int& index) const;

	struct greaterThan {
		bool operator() (const GenomeMatch& g1, const GenomeMatch& g2){
			return (g1.percentMatch > g2.percentMatch);
		}
	};
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength) : m_minSearch(minSearchLength) {}

// Add a specified genome to a vector of genomes and the trie
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	gvec.push_back(genome); // adds to vector
	string s = "";
	int i = 0;
	while (genome.extract(i, minimumSearchLength(), s)) {
		gtrie.insert(s, segValue(i, genome.name()));		// inserts into the tree with a value containing a position and name
		i++;
	}
}

// Returns the minimum search length in the genome matcher
int GenomeMatcherImpl::minimumSearchLength() const
{
	return m_minSearch; 
}

// Finds a fragment of DNA bases in each genome where is exists and adds the longest match to a vector
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (fragment.size() < minimumLength || minimumLength < minimumSearchLength()) return false;
	bool oneMatch = false;
	vector<segValue> values = gtrie.find(fragment.substr(0, minimumSearchLength()), exactMatchOnly); // Finds all the matches
	const Genome* gp = nullptr;
	string possible;
	int snip;
	for (vector<segValue>::iterator i = values.begin(); i != values.end(); i++) { // Loop through matches
		possible = "";
		snip = 0;
		vector<Genome>::const_iterator j = gvec.begin();
		for (; j != gvec.end(); j++)			// Loop through the genome vector to find the genome with the correct name
			if (i->m_name == j->name())
				gp = &(*j);
		string rest = "";
		int k = i->m_pos;
		gp->extract(k, gp->length() - k, rest);   // Isolates the genome bases after the position
		for (int l = 0; l < fragment.size() && l < rest.size() && snip < 2; l++) { // simultaneously loops through the fragment and the genome
			if (fragment[l] != rest[l]) {   // if a character doesn't match
				if (exactMatchOnly) break;	// if exact match is necessary move to the next value
				else snip++;				// if exact match isn't necessary add an incorrect tick
			}
			if (snip >= 2) break;			// if there are two incorrect ticks move to the next value
			string c(1, fragment[l]);
			possible += c;					// creates a possible match string
			if (possible.size() >= minimumLength) {	// if the possible string exceeds the minimum length, it's a match
				int index;
				if (matches.empty() || !containsGenome(matches, gp->name(), index)) // If the matches vector is empty or the genome has not been inserted before, insert the new dna match
					matches.push_back(createDNA(gp->name(), possible.size(), k));
				else if (containsGenome(matches, gp->name(), index) &&
					possible.size() > matches[index].length) // If the genome is already present and the new dna match is longer, insert it into the matches vector
					matches[index] = createDNA(gp->name(), possible.size(), k);
				oneMatch = true;
			}
		}
	}
	return oneMatch;
}

// Determines if a query genome matches a certain percentage within the genomes in the library
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	if (fragmentMatchLength < minimumSearchLength()) return false;
	bool oneMatch = false;
	int numSeqs = query.length() / fragmentMatchLength;
	map<string, int> matchMap;
	for (int i = 0; i < numSeqs; i++) { // Loop through the query for the number of sequences
		string frag = "";
		query.extract(i*fragmentMatchLength, fragmentMatchLength, frag); // extract the segment of the query to analyze
		vector<DNAMatch> matches;
		if (findGenomesWithThisDNA(frag, fragmentMatchLength, exactMatchOnly, matches)) { // Maps matches to string and amount of integer matches
			for (vector<DNAMatch>::iterator p = matches.begin(); p != matches.end(); p++)
				matchMap[p->genomeName] += 1;
		}
	}
	results.clear();
	for (map<string, int>::iterator i = matchMap.begin(); i != matchMap.end(); i++) {
		GenomeMatch genX = createGenomeMatch(i->first, i->second, numSeqs);
		if (genX.percentMatch >= matchPercentThreshold) {
			results.push_back(genX);		// Adds a genome match to the results vector if it has a match percentage greater than the threshhold
			oneMatch = true;
		}
	}
	sort(results.begin(), results.end(), greaterThan());
	return oneMatch;
}

// Creates a DNA Match with a specified name, length and position
DNAMatch GenomeMatcherImpl::createDNA(string name, int length, int position) const {
	DNAMatch dna;
	dna.genomeName = name;
	dna.length = length;
	dna.position = position;
	return dna;
}

// Creates a Genome Match with a specified name, number of matches and total number of sequences
GenomeMatch GenomeMatcherImpl::createGenomeMatch(string name, int matches, int totalNum) const {
	GenomeMatch gm;
	gm.genomeName = name;
	gm.percentMatch = (matches / (double)totalNum) * 100;
	return gm;
}

// Loop through the matches vector and returns the index of the matchines genome
bool GenomeMatcherImpl::containsGenome(vector<DNAMatch> matches, string name, int& index) const {
	for (int i = 0; i < matches.size(); i++) {
		if (matches[i].genomeName == name) {
			index = i;
			return true;
		}
	}
	return false;
}



//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
	m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
	delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
	m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
	return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
