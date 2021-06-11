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
 if ( d < 0 )
 {
   return 0x49; // if below 0, print "I" of the word "MIN"
 }
 elseif (d >= 0 && d < 1000)
 {
  a = d % 10; // a = units digit
  a = a + 0x30;
  return a;
 }
 elseif (d >= 1000)
 {
  return 0x41; // if above 3-digits, print "A" of the word "MAX"
 }
}

dist_ASCII_b2(double d)
{
 int a;
 int b;
 if (d >= 1000 || d < 0)
 {
  return 0x4D; // if below 0 or above 3-digits, print "M" of the word "MAX" or "MIN"
 }
 elseif (d >= 0 && d < 1000)
 {
  a = d % 100; // a = rightmost 2 digits
  b = d % 10; // b = units digit
  a = d - b; // tenth digit
  a = a + 0x30;
  return a;
 }

dist_ASCII_b3(double d)
{
 int a;
 int b;
 if (d >= 1000 || d < 0)
 {
  return 0x00; // print empty space since "MAX" and "MIN" need only 3 spaces
 }
 if (d >= 0 && d < 1000)
 {
  b = d % 100; // b = rightmost 2 digits
  a = d - b; // a = 3rd digit
  a = a + 0x30;
  return a;
}

