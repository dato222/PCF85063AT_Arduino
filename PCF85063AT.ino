const int  TimeAddress = 81;
//****************************************************************************************
void setPCF85063ATtime(byte second, byte minute, byte hour, 
byte dom, byte dow, byte month, byte year)
{
  Wire.beginTransmission(TimeAddress);
  Wire.write(0x04);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dom)); //day of month, 1-31
  Wire.write(decToBcd(dow)); //day of week, 0-Sunday
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}
//****************************************************************************************
void readPCF85063ATtime(byte* tbuf)//time buffer
{
  //if(sizeof(tbuf)<7) return;
  //Serial2.println(sizeof(tbuf));
  byte n = 0;
  Wire.beginTransmission(TimeAddress);
  Wire.write(0x04);
  Wire.endTransmission();
  Wire.requestFrom(TimeAddress, 7);
  
  while(Wire.available())
  {
    tbuf[n] = Wire.read();
    n++;
  }

  tbuf[0] = (10*((tbuf[0]>>4) & 7)+(tbuf[0] & 15));//second
  tbuf[1] = (10*(tbuf[1]>>4)+(tbuf[1] & 15));//minute
  tbuf[2]   = (10*((tbuf[2]>>4) & 3)+(tbuf[2] & 15));//hour
  tbuf[3]=(10*(tbuf[3]>>4)+(tbuf[3]&15));//day of month
  tbuf[4]=tbuf[4];//day of week
  tbuf[5]=(10*(tbuf[5]>>4)+(tbuf[5]&15));//month
  tbuf[6]=(10*(tbuf[6]>>4)+(tbuf[6]&15));//year
}
//****************************************************************************************
void readPCF85063ATReg(byte addr, byte count, byte* tbuf)
{
  byte n = 0;
  Wire.beginTransmission(TimeAddress);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(TimeAddress, count);
  
  while(Wire.available())
  {
    tbuf[n] = Wire.read();
    n++;
  }
}
//****************************************************************************************
void writePCF85063ATReg(byte addr, byte value)
{
  Wire.beginTransmission(TimeAddress);
  Wire.write(addr);
  Wire.write(value);
  Wire.endTransmission();
}
//****************************************************************************************
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}
