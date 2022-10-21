// Copyright 2009-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "engine.h"
#include "scratch.h"
#include "concat_conv.h"

namespace oidn {

  Ref<Buffer> Engine::newBuffer(size_t byteSize, Storage storage)
  {
    return makeRef<USMBuffer>(this, byteSize, storage);
  }

  Ref<Buffer> Engine::newBuffer(void* ptr, size_t byteSize)
  {
    return makeRef<USMBuffer>(this, ptr, byteSize);
  }

  Ref<ScratchBuffer> Engine::newScratchBuffer(size_t byteSize)
  {
    auto scratchManager = scratchManagerWp.lock();
    if (!scratchManager)
      scratchManagerWp = scratchManager = std::make_shared<ScratchBufferManager>(this);
    return makeRef<ScratchBuffer>(scratchManager, byteSize);
  }

  std::shared_ptr<Tensor> Engine::newTensor(const TensorDesc& desc, Storage storage)
  {
    return std::make_shared<GenericTensor>(this, desc, storage);
  }

  std::shared_ptr<Tensor> Engine::newTensor(const TensorDesc& desc, void* data)
  {
    return std::make_shared<GenericTensor>(this, desc, data);
  }

  std::shared_ptr<Tensor> Engine::newTensor(const Ref<Buffer>& buffer, const TensorDesc& desc, size_t byteOffset)
  {
    assert(buffer->getEngine() == this);
    return std::make_shared<GenericTensor>(buffer, desc, byteOffset);
  }

  std::shared_ptr<ConcatConv> Engine::newConcatConv(const ConcatConvDesc& desc)
  {
    return std::make_shared<CHWConcatConv>(this, desc);
  }

  void* Engine::malloc(size_t byteSize, Storage storage)
  {
    return alignedMalloc(byteSize);
  }

  void Engine::free(void* ptr, Storage storage)
  {
    alignedFree(ptr);
  }

  void Engine::memcpy(void* dstPtr, const void* srcPtr, size_t byteSize)
  {
    std::memcpy(dstPtr, srcPtr, byteSize);
  }

  Storage Engine::getPointerStorage(const void* ptr)
  {
    return Storage::Host;
  }

} // namespace oidn
