#include <future>
#include "raw_block_iter.h"

namespace leveldb {

RawBlockIterator::RawBlockIterator(SequentialFile* file): stream_(file) {
  count = 0;
  while (!stream_.eof()) {
    Slice key = stream_.Get();
    Slice value = stream_.Get();
    vector_.push_back({key, value});
  }
  iterator_ = vector_.begin();
  fnumber = 0;
}

RawBlockIterator::~RawBlockIterator() {
}

bool RawBlockIterator::Valid() const {
  return count < vector_.size();
  return iterator_ != vector_.end();
}

void RawBlockIterator::SeekToFirst() {
  iterator_ = vector_.begin();
  count = 0;
}

void RawBlockIterator::SeekToLast() {
  iterator_ = vector_.end();
  count = vector_.size();
}

void RawBlockIterator::Seek(const Slice &target) {
}

void RawBlockIterator::Next() {
  ++iterator_;
  ++count;
}

void RawBlockIterator::Prev() {
  --iterator_;
  --count;
}

Slice RawBlockIterator::key() const {
  return iterator_->first;
}

Slice RawBlockIterator::value() const {
  return iterator_->second;
}

Status RawBlockIterator::status() const {
  return stream_.status();
}
void RawBlockIterator::SetFileNumber(uint64_t number) {
  fnumber = number;
}

uint64_t RawBlockIterator::GetFileNumber() {
  return fnumber;
}

}
