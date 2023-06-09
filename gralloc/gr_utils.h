/*
 * Copyright (c) 2011-2016,2018,2019 The Linux Foundation. All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __GR_UTILS_H__
#define __GR_UTILS_H__

#include <android/hardware/graphics/common/1.2/types.h>
#include "gralloc_priv.h"
#include "qdMetaData.h"

#define SZ_2M 0x200000
#define SZ_1M 0x100000
#define SZ_4K 0x1000

#define SIZE_4K 4096
#define SIZE_8K 4096

#ifdef MASTER_SIDE_CP
#define SECURE_ALIGN SZ_4K
#else
#define SECURE_ALIGN SZ_1M
#endif

#define INT(exp) static_cast<int>(exp)
#define UINT(exp) static_cast<unsigned int>(exp)

using android::hardware::graphics::common::V1_1::BufferUsage;

namespace gralloc {
struct BufferInfo {
  BufferInfo(int w, int h, int f, uint64_t usage = 0)
      : width(w), height(h), format(f), layer_count(1), usage(usage) {}
  int width;
  int height;
  int format;
  int layer_count;
  uint64_t usage;
};

template <class Type1, class Type2>
inline Type1 ALIGN(Type1 x, Type2 align) {
  return (Type1)((x + (Type1)align - 1) & ~((Type1)align - 1));
}

bool IsYuvFormat(int format);
bool IsCompressedRGBFormat(int format);
bool IsUncompressedRGBFormat(int format);
uint32_t GetBppForUncompressedRGB(int format);
bool CpuCanAccess(uint64_t usage);
bool CpuCanRead(uint64_t usage);
bool CpuCanWrite(uint64_t usage);
int GetBpp(int format);
unsigned int GetSize(const BufferInfo &d, unsigned int alignedw, unsigned int alignedh);
void GetBufferSizeAndDimensions(const BufferInfo &d, unsigned int *size, unsigned int *alignedw,
                                unsigned int *alignedh);
void GetBufferSizeAndDimensions(const BufferInfo &d, unsigned int *size, unsigned int *alignedw,
                                unsigned int *alignedh, GraphicsMetadata *graphics_metadata);
void GetCustomDimensions(private_handle_t *hnd, int *stride, int *height);
void GetColorSpaceFromMetadata(private_handle_t *hnd, int *color_space);
void GetAlignedWidthAndHeight(const BufferInfo &d, unsigned int *aligned_w,
                              unsigned int *aligned_h);
int GetYUVPlaneInfo(const private_handle_t *hnd, struct android_ycbcr ycbcr[2]);
int GetRgbDataAddress(private_handle_t *hnd, void **rgb_data);
bool IsUBwcFormat(int format);
bool IsUBwcSupported(int format);
bool IsUBwcEnabled(int format, uint64_t usage);
void GetYuvUBwcWidthAndHeight(int width, int height, int format, unsigned int *aligned_w,
                              unsigned int *aligned_h);
void GetYuvSPPlaneInfo(uint64_t base, uint32_t width, uint32_t height, uint32_t bpp,
                       struct android_ycbcr *ycbcr);
void GetYuvUbwcSPPlaneInfo(uint64_t base, uint32_t width, uint32_t height, int color_format,
                           struct android_ycbcr *ycbcr);
void GetYuvUbwcInterlacedSPPlaneInfo(uint64_t base, uint32_t width, uint32_t height,
                                     int color_format, struct android_ycbcr ycbcr[2]);
void GetRgbUBwcBlockSize(uint32_t bpp, int *block_width, int *block_height);
unsigned int GetRgbUBwcMetaBufferSize(int width, int height, uint32_t bpp);
unsigned int GetUBwcSize(int width, int height, int format, unsigned int alignedw,
                         unsigned int alignedh);
int GetBufferLayout(private_handle_t *hnd, uint32_t stride[4], uint32_t offset[4],
                    uint32_t *num_planes);
uint32_t GetDataAlignment(int format, uint64_t usage);

void GetGpuResourceSizeAndDimensions(const BufferInfo &info, unsigned int *size,
                                     unsigned int *alignedw, unsigned int *alignedh,
                                     GraphicsMetadata *graphics_metadata);
bool CanUseAdrenoForSize(int buffer_type, uint64_t usage);
bool GetAdrenoSizeAPIStatus();
bool IsGPUFlagSupported(uint64_t usage);
int GetBufferType(int inputFormat);
}  // namespace gralloc

#endif  // __GR_UTILS_H__
