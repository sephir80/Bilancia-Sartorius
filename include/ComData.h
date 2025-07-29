    const byte command[] = {0x1B, 0x6B, 0x50, 0x5F, 0x0D, 0x0A};
class ComData
{
  private:
  public:
    ComData();
    void Begin();
    String* Receive();
    void Send(String* str);
    void SendTest(String str);
};