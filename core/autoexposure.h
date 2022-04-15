// Copyright 2009-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "op.h"
#include "image.h"

namespace oidn {

  class Autoexposure : public virtual Op
  {
  public:
    static constexpr int maxBinSize = 16;
    static constexpr float key = 0.18f;
    static constexpr float eps = 1e-8f;

    Autoexposure(const ImageDesc& srcDesc)
      : srcDesc(srcDesc)
    {
      numBinsH = ceil_div(srcDesc.getH(), maxBinSize);
      numBinsW = ceil_div(srcDesc.getW(), maxBinSize);
      numBins = numBinsH * numBinsW;
    }
    
    void setSrc(const std::shared_ptr<Image>& src)
    {
      assert(src->getW() == srcDesc.getW() && src->getH() == srcDesc.getH());
      this->src = src;
    }
    
    // Returns pointer to the result in device memory
    virtual const float* getResult() const = 0;

  protected:
    ImageDesc srcDesc;
    std::shared_ptr<Image> src;

    int numBinsH;
    int numBinsW;
    int numBins;
  };

} // namespace oidn
