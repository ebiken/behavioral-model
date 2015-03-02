#ifndef _BM_BYTECONTAINER_H_
#define _BM_BYTECONTAINER_H_

#include <vector>
#include <iterator>
#include <string>

#include <boost/functional/hash.hpp>

using std::vector;

class ByteContainer
{
public:
  typedef vector<char>::iterator iterator;
  typedef vector<char>::const_iterator const_iterator;
  // typedef std::reverse_iterator<iterator> reverse_iterator;
  // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef vector<char>::reference reference;
  typedef vector<char>::const_reference const_reference;
  typedef size_t size_type;

  public:
  ByteContainer() {}

  ByteContainer(int nbytes)
    : bytes(vector<char>(nbytes)) {}

  ByteContainer(const vector<char> &bytes)
    : bytes(bytes) {}

  ByteContainer(const char *bytes, size_t nbytes)
    : bytes(vector<char>(bytes, bytes + nbytes)) {}

  static char char2digit(char c) {
    if(c >= '0' && c <= '9')
      return (c - '0');
    if(c >= 'A' && c <= 'F')
      return (c - 'A' + 10);
    if(c >= 'a' && c <= 'f')
      return (c - 'a' + 10);
    assert(0);
    return 0;
  }

  ByteContainer(const std::string hexstring) {
    std::vector<char> bytes;
    size_t idx = 0;

    assert(hexstring[idx] != '-');

    if(hexstring[idx] == '0' && hexstring[idx + 1] == 'x') {
      idx += 2;
    }
    size_t size = hexstring.size();
    assert((size - idx) > 0);

    if((size - idx) % 2 != 0) {
      char c = char2digit(hexstring[idx++]);
      bytes.push_back(c);
    }

    for(; idx < size; ) {
      char c = char2digit(hexstring[idx++]) << 4;
      c += char2digit(hexstring[idx++]);
      bytes.push_back(c);
    }
  }

  size_type size() const noexcept { return bytes.size(); }

  // iterators
  iterator begin() { return bytes.begin(); }

  const_iterator begin() const { return bytes.begin(); }

  iterator end() { return bytes.end(); }

  const_iterator end() const { return bytes.end(); }

  // reverse_iterator rbegin() { return bytes.rbegin(); }

  // const_reverse_iterator rbegin() const { return bytes.rbegin(); }

  // reverse_iterator rend() { return bytes.rend(); }

  // const_reverse_iterator rend() const { return bytes.rend(); }

  // const_iterator cbegin() const { return bytes.cbegin(); }

  // const_iterator cend() const { return bytes.cend(); }

  // const_reverse_iterator crbegin() const { return bytes.crbegin(); }

  // const_reverse_iterator crend() const { return bytes.crend(); }

  ByteContainer &append(const ByteContainer &other) {
    bytes.insert(end(), other.begin(), other.end());
    return *this;
  }

  reference operator[](size_type n) {
    assert(n < size());
    return bytes[n];
  }

  const_reference operator[](size_type n) const {
    assert(n < size());
    return bytes[n];
  }

  char* data() noexcept {
    return bytes.data();
  }

  const char* data() const noexcept {
    return bytes.data();
  }

  bool operator==(const ByteContainer& other) const {
    return bytes == other.bytes;
  }

  bool operator!=(const ByteContainer& other) const {
    return !(*this == other);
  }

  // TODO: implement reserve

private:
  vector<char> bytes;
};

struct ByteContainerKeyHash {
  std::size_t operator()(const ByteContainer& b) const {
    // Murmur, boost::hash_range or Jenkins?
    return boost::hash_range(b.begin(), b.end());
  }
};

#endif