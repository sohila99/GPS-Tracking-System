dist_ASCII_b0(double d)
{
 if ( d < 0 )
 {
  return 0x4E; // if below 0, print "N" of the word "MIN"
 }
 elseif ( d >= 0 && d < 1000)
 {
  return 0x6D; // if in the correct range, print "m" for meters
 }
 elseif (d >= 1000)
  return 0x58; // if above 3-digits, print "X" of the word "MAX"
}

dist_ASCII_b1(double d)
{
 int a;
 int b;
 if ( d < 0 )
 {
   return 0x49; // if below 0, print "I" of the word "MIN"
 }
 elseif (d < 10 && d >= 0)
 {
  a = d + 0x30; // if the number is already 1-digit, print it
  return a;
 }
 eiseif (d < 1000 && d >= 10)
 {
  a = d % 10; // if the number is 2-digits or 3-digits, a = units digit
  return a;
 }
 elseif (d >= 1000)
 {
  return 0x41; // if above 3-digits, print "A" of the word "MAX"
 }
}
//stop
dist_ASCII_b2(double d)
{
 int a;
 int b;
 if ( d < 0 || d >= 10000)
 {
  return 0x4D; // if below 0 or above 3-digits, print "M" of the word "MAX" or "MIN"
 }
 elseif ( d >= 0 && d < 10)
 {
  return 0x30; // if the numbeer is 1-digit, then tens digit = 0
 }
 elseif ( d >= 10 && d < 100)
 {
  
 
   
}

dist_ASCII_b3(double d)
{
 int a;
 int b;
 if ( d < 0 )
}

