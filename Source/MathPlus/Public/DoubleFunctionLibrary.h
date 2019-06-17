TArray<uint8> DoubleToBytes(const double& Value)
{

}

double BytesToDouble(const TArray<uint8>& Value)
{


int64 BytesToLong(const TArray<uint8>& Value)
{
    auto Index = 0;
    auto Length = 0x7FFFFFFF;
    Length = Value.Num() - Index;
    return (((int64)Value[Index + 0] << 56));
}