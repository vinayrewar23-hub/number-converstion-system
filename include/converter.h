#ifndef CONVERTER_H
#define CONVERTER_H

void decimaltobase(long long decimalnum, int base, char result[]);
long long basetodecimal(const char* numstr, int base);
void displaymenu(void);
void decimaltoall(void);
void anybasetodecimal(int base);

#endif
