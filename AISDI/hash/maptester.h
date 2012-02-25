#ifndef MAP_TESTER_H_
#define MAP_TESTER_H_

#include <vector>
#include <string>

class MapTester
{
   std::map<std::string, int> sm;

protected:
   bool insert(const std::string& s, int i);
   unsigned remove(const std::string& s);
   void modifyOrAdd(const std::string& s, int i);
   int read(const std::string& s);
   bool find(const std::string& s);
   size_t size();

private:
   bool _insert(const std::string& s, int i);
   unsigned _remove(const std::string& s);
   void _modifyOrAdd(const std::string& s, int i);
   int _read(const std::string& s);
   bool _find(const std::string& s);

public:
   void test();

   MapTester(std::istream& input);
};

#endif
