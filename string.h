#include <cstring>
#include <iostream>

class String {
private:
    char* string_;
    size_t length_;
    size_t capacity_;
    String(int cnt): string_(new char[cnt + 1]), length_(cnt), capacity_(cnt + 1) {}
    String(char* st, int length, int cap) : string_(st), length_(length), capacity_(cap) {}
public:
    String(const char* st) : String(static_cast<int>(strlen(st))) {
      memcpy(string_, st, length_ + 1);
    }
    String(const String& s) : string_(new char[s.capacity_]), length_(s.length_), capacity_(s.capacity_) {
      memcpy(string_, s.string_, length_ + 1);
    }
    String(char ch) : String(1) {
      string_[0] = ch;
      string_[1] = '\0';
    }
    String(int n, char c) : String(n) {
      std::fill(string_, string_ + length_, c);
      string_[length_] = '\0';
    }
    String() : string_(new char[1]), length_(0), capacity_(1) {
      string_[0] = '\0';
    }
    String& operator=(const String& s) {
      if (this == &s) {
        return *this;
      }
      if (capacity_ < s.capacity_) {
        delete[] string_;
        string_ = new char[s.capacity_];
      }
      capacity_ = s.capacity_;
      length_ = s.length_;
      memcpy(string_, s.string_, length_ + 1);
      return *this;
    }
    void reallocate(int cnt) {
      char* temp = new char[cnt];
      if (string_ != nullptr) {
        memcpy(temp, string_, length_ + 1);
        delete[] string_;
      }
      string_ = temp;
      capacity_ = cnt;
    }
    const char& operator[](int i) const {return string_[i];}
    char& operator[](int i) {return string_[i];}
    long unsigned int length() const {
      return length_;
    }
    long unsigned int size() const {return length_;}
    long unsigned int capacity() const {return capacity_ - 1;}
    void push_back(char ch) {
      if (length_ >= capacity_ - 1) {
        reallocate(capacity_ * 2 + 1);
      }
      string_[length_] = ch;
      ++length_;
      string_[length_] = '\0';
    }
    void pop_back() {
      string_[length_ - 1] = '\0';
      --length_;
    }
    char& back() {return string_[length_ - 1];}
    const char& back() const {return string_[length_ - 1];}
    char& front() {return string_[0];}
    const char& front() const {return string_[0];}
    String& operator+=(const String& other)  {
      if (other.length_ + length_ >= capacity_) {
        while (other.length_ + length_ >= capacity_) {
          capacity_ *= 2;
        }
        reallocate(capacity_);
      }
      memcpy(string_ + length_, other.string_, other.length_);
      length_ += other.length_;
      string_[length_] = '\0';
      return *this;
    }
    String& operator+=(char ch) {
      push_back(ch);
      return *this;
    }
    long unsigned int find(const String& st) const {
      for (size_t i = 0; i < length_ - st.length_ + 1; ++i) {
        if (memcmp(string_ + i, st.string_, st.length_) == 0) {
          return i;
        }
      }
      return length_;
    }
    long unsigned int rfind(const String& st) const {
      for (int i = length_ - st.length_; i >= 0; --i) {
        if (memcmp(string_ + i, st.string_, st.length_) == 0) {
          return i;
        }
      }
      return length_;
    }
    String substr(int pos, int cnt) const {
      char* temp = new char[cnt + 1];
      memcpy(temp, string_ + pos, cnt);
      temp[cnt] = '\0';
      return String(temp, cnt, cnt + 1);
    }
    bool empty() {
      return length_ == 0;
    }
    void clear() {
      length_ = 0;
      string_[0] = '\0';
    }
    void shrink_to_fit() {
      if (capacity_ != length_ + 1) {
        capacity_ = length_ + 1;
        char *temp = new char[capacity_];
        memcpy(temp, string_, length_);
        delete[] string_;
        string_ = temp;
        string_[length_] = '\0';
      }
    }
    char* data() {
      return string_;
    }
    const char* data() const {
      return string_;
    }
    ~String() {delete[] string_;}
};
bool operator==(const String& s1, const String& s2) {
  if (s1.size() != s2.size()) {
    return false;
  }
  return strcmp(s1.data(), s2.data()) == 0;
}
bool operator!=(const String& s1, const String& s2) {return !(s1 == s2);}
bool operator<(const String& s1, const String& s2) {return strcmp(s1.data(), s2.data()) < 0;}
bool operator<=(const String& s1, const String& s2) {return (s1 < s2);}
bool operator>(const String& s1, const String& s2) {return !(s1 <= s2);}
bool operator>=(const String& s1, const String& s2) {return !(s1 < s2);}
std::ostream& operator<<(std::ostream& os, const String& st) {
  os << st.data();
  return os;
}
std::istream& operator>>(std::istream& is, String& st) {
  st.clear();
  char ch;
  is.get(ch);
  while (!isspace(ch) && !is.eof()) {
    st.push_back(ch);
    is.get(ch);
  }
  return is;
}
String operator+(const String& s1, const String& s2) {
  String s3 = s1;
  s3 += s2;
  return s3;
}
