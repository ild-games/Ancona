#pragma once

#include <memory>
#include <string>

namespace ildhal
{

namespace priv
{
class RapidJsonOStreamWrapperImpl;
} // namespace prive

class RapidJsonOStreamWrapper
{
  public:
    typedef char Ch;

    RapidJsonOStreamWrapper();
    bool LoadFromFile(const std::string & filename);
    char Peek() const;
    char Take();
    size_t Tell();
    char* PutBegin();
    void Put(char c);
    void Flush();
    size_t PutEnd(char* begin);

    priv::RapidJsonOStreamWrapperImpl & rapidJsonStreamWrapperImpl() const { return *_pimpl; }

  private:
    std::unique_ptr<priv::RapidJsonOStreamWrapperImpl> _pimpl;
};

} // namespace ildhal
