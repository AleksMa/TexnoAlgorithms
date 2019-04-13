#include <vector>

using std::vector;

class OutBitStream {
 public:
  OutBitStream();

  void WriteBit(unsigned char bit);
  void WriteByte(unsigned char byte);

  const vector<unsigned char> &GetBuffer() { return buffer; };
  int GetBitsCount() const { return bitsCount; };

 private:
  vector<unsigned char> buffer;
  int bitsCount;
};

void OutBitStream::WriteBit(unsigned char bit) {
  if (bitsCount + 1 > buffer.size() * 8)
    buffer.push_back(0);

  if (bit != 0)
    buffer[buffer.size() - 1] |= 1 << bitsCount % 8;

  bitsCount++;
}

void OutBitStream::WriteByte(unsigned char byte) {
  if (bitsCount % 8 == 0) {
    buffer.push_back(byte);
    bitsCount += 8;
    return;
  }

  buffer.back() |= byte << (bitsCount % 8);
  buffer.push_back(byte >> (8 - bitsCount % 8));
  bitsCount += 8;

}












