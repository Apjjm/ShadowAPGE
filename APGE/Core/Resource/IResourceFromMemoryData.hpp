#ifndef IRESOURCEFROMMEMORYDATA_HPP
#define IRESOURCEFROMMEMORYDATA_HPP
#include "APGE/Core/CoreTypes.hpp"

namespace APGE
{
namespace Resource
{
class IResourceFromMemoryData
{
public:
  IResourceFromMemoryData() : rawDataPtr_(), rawDataLength_(0)
  {
  }

  IResourceFromMemoryData(std::shared_ptr<const void> rawDataPtr, std::size_t rawDataLength)
    : rawDataPtr_(rawDataPtr), rawDataLength_(rawDataLength)
  {
  }

  inline std::shared_ptr<const void> getRawDataPointer()
  {
    return rawDataPtr_;
  }

  inline std::size_t getRawDataLength()
  {
    return rawDataLength_;
  }

  inline void setRawDataBlock(std::shared_ptr<const void> rawDataPtr, std::size_t rawDataLength)
  {
    rawDataPtr_ = rawDataPtr;
    rawDataLength_ = rawDataLength;
  }

private:
  std::shared_ptr<const void> rawDataPtr_;
  std::size_t rawDataLength_;
};

}
}
#endif // IRESOURCEFROMMEMORYDATA_HPP
