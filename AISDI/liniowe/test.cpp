//#include "aisdihashmap.h"

#include <map>
using namespace std;
#define AisdiMap map

#ifdef _SUNOS
#include "/home/common/dyd/aisdi/hash/maptester.h"
#else
#include "maptester.h"
#endif

static AisdiMap<string, int> m;

bool MapTester::insert(const string& s, int i) {return (m.insert(make_pair(s, i))).second;}
unsigned MapTester::remove(const string& s) {return (unsigned)m.erase(s);}
void MapTester::modifyOrAdd(const string& s, int i) {m[s]=i;}
int MapTester::read(const string& s) {return m[s];}
bool MapTester::find(const string& s) { return m.find(s)!=m.end(); }
size_t MapTester::size() { return m.size(); }
