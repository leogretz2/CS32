#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
	GenomeImpl(const string& nm, const string& sequence);
	static bool load(istream& genomeSource, vector<Genome>& genomes);
	int length() const;
	string name() const;
	bool extract(int position, int length, string& fragment) const;
private:
	string m_name;
	string m_seq;
};

bool doesContainWrong(string s);

GenomeImpl::GenomeImpl(const string& nm, const string& sequence) : m_name(nm), m_seq(sequence) {}

// Loads a number of genomes into a vector, based on a text file and returns false if there is a formatting error
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
	genomes.clear();
	int lineCount = 0;
	string s;
	string name;
	string sequence;
	while (getline(genomeSource, s)) {
		lineCount++;
		if (s == "") return false;	// If the line is empty, error
		switch (s[0]) {
		case '>':
			if(lineCount == 1 && genomeSource.peek() != -1 && s != ">")	// If the name starts with a ">" and contains things after it and it at the start of a genome
				name = s.substr(1, s.size() - 1);	// If valid name, add it the name
			else return false;		
			break;
		case 'A': case 'T': case 'G': case 'C': case 'N': case 'a': case 't': case 'g': case 'c': case 'n':
			if (s.size() > 80 || lineCount == 1) return false;	// If the size is too big, or there is no name before it
			if (s.size() >= 3 && s[2] == '_') return false;		// If the line starts with a letter but is a name
			if (doesContainWrong(s)) return false;				// If the non-name line contains an invalid letter
			for (int i = 0; i < s.size(); i++)					// Convert all letters to upper case
				s[i] = toupper(s[i]);
			sequence += s;						// If valid non-name line add it to the sequence
			break;
		default:
			return false;
			break;
		}
		char next = genomeSource.peek();
		if (next == '>' || next == -1) {		// If the next line is a name or the the file is done add the genome to the vector
			genomes.push_back(Genome(name, sequence));
			lineCount = 0;
			name = "";
			sequence = "";
		}
	}
	return true;
}

int GenomeImpl::length() const
{
	return m_seq.size();
}

string GenomeImpl::name() const
{
	return m_name;
}

// Extracts a substring from the genome sequence
bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	if (position + length > m_seq.size() || position < 0) return false;		// If length extends past end of sequence
	fragment = m_seq.substr(position, length);			// Create substring of sequence
	return true; 
}

// Returns whether a non-name line contains a letter other than A, G, T, C, or N. 
bool doesContainWrong(string s) {
	for (int i = 0; i < s.size(); i++) 
		if (s[i] < 'A' || s[i] == 'B' || (s[i] > 'C' && s[i] < 'G') || (s[i] > 'G' && s[i] < 'N') ||
			(s[i] > 'N' && s[i] < 'T') || (s[i] > 'T' && s[i] < 'a') || s[i] == 'b' || 
			(s[i] > 'c' && s[i] < 'g') || (s[i] > 'g' && s[i] < 'n') || (s[i] > 'n' && s[i] < 't') ||
			s[i] > 't')
			return true;
	return false;
}


//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
	m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
	delete m_impl;
}

Genome::Genome(const Genome& other)
{
	m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
	GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
	delete m_impl;
	m_impl = newImpl;
	return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
	return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
	return m_impl->length();
}

string Genome::name() const
{
	return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
	return m_impl->extract(position, length, fragment);
}
