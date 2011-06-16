// Copyright (c) 2011 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS.  All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.

#ifndef MKVMUXERUTIL_HPP
#define MKVMUXERUTIL_HPP

#include "mkvmuxertypes.hpp"

namespace mkvmuxer
{

class IMkvWriter;

// Writes out |value| in Big Endian order. Returns 0 on success. 
int SerializeInt(IMkvWriter* writer, int64 value, int size);

// Returns the size in bytes of the element. |master| must be set to true if
// the element is an Mkv master element.
// TODO: Change these functions so they are master element aware.
uint64 EbmlElementSize(uint64 type, uint64 value, bool master);
uint64 EbmlElementSize(uint64 type, float value, bool master);
uint64 EbmlElementSize(uint64 type, const char* value, bool master);
uint64 EbmlElementSize(uint64 type,
                       const uint8* value,
                       uint64 size,
                       bool master);

// Creates an EBML coded number from |value| and writes it out. The size of
// the coded number is deteremined by the value of |value|. |value| must not
// be in a coded form. Returns 0 on success.
int WriteUInt(IMkvWriter* pWriter, uint64 value);

// Creates an EBML coded number from |value| and writes it out. The size of
// the coded number is deteremined by the value of |size|. |value| must not
// be in a coded form. Returns 0 on success.
int WriteUIntSize(IMkvWriter* pWriter, uint64 value, int size);

// Output an Mkv master element. Returns true if the element was written.
bool WriteEbmlMasterElement(IMkvWriter* pWriter, uint64 value, uint64 size);

// Output an Mkv non-master element. Returns true if the element was written.
bool WriteEbmlElement(IMkvWriter* pWriter, uint64 type, uint64 value);
bool WriteEbmlElement(IMkvWriter* pWriter, uint64 type, float value);
bool WriteEbmlElement(IMkvWriter* pWriter, uint64 type, const char* value);
bool WriteEbmlElement(IMkvWriter* pWriter,
                      uint64 type,
                      const uint8* value,
                      uint64 size);

uint64 WriteSimpleBlock(IMkvWriter* pWriter,
                        const uint8* data,
                        uint64 length,
                        char track_number,
                        short timestamp,
                        bool is_key);

// Output a void element. |size| must be the entire size in bytes that will be
// void. The function will calculate the size of the void header and subtract
// it from |size|.
uint64 WriteVoidElement(IMkvWriter* pWriter, uint64 size);

// Returns the version number of the muxer in |major|, |minor|, |build|,
// and |revision|.
void GetVersion(int& major, int& minor, int& build, int& revision);

}  //end namespace mkvmuxer

#endif //MKVMUXERUTIL_HPP