//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007-2016 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <core/library/track/Track.h>
#include <core/library/ILibrary.h>
#include <core/sdk/ITrackListEditor.h>

#include <unordered_map>
#include <list>

namespace musik { namespace core {
    class TrackList : public musik::core::sdk::ITrackListEditor {
        public:
            TrackList(LibraryPtr library);
            virtual ~TrackList();

            size_t Count();
            TrackPtr Get(size_t index);
            DBID GetId(size_t index);
            int IndexOf(DBID id);

            void ClearCache();
            void Swap(TrackList& list);
            void CopyFrom(TrackList& from);

            virtual void Add(const DBID id);
            virtual void Clear();
            virtual void Insert(unsigned long long id, size_t index);
            virtual void Swap(size_t index1, size_t index2);
            virtual void Move(size_t from, size_t to);
            virtual void Delete(size_t index);
            virtual void Shuffle();

        private:
            typedef std::list<DBID> CacheList;
            typedef std::pair<TrackPtr, CacheList::iterator> CacheValue;
            typedef std::unordered_map<DBID, CacheValue> CacheMap;

            TrackPtr GetFromCache(DBID key);
            void AddToCache(DBID key, TrackPtr value);

            /* lru cache structures */
            CacheList cacheList;
            CacheMap cacheMap;

            std::vector<DBID> ids;
            LibraryPtr library;
    };
} }
