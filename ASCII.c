char dist_ASCII_b0(int d)
{
    if (d < 0)
    {
        return 0x4E; // if below 0, print "N" of the word "MIN"
    }
    else if (d >= 0 && d < 1000)
    {
        return 0x6D; // if in the correct range, print "m" for meters
    }
    else if (d >= 1000)
    {
        return 0x58; // if above 3-digits, print "X" of the word "MAX"
    }
}

char dist_ASCII_b1(int d)
{
    int a;
    if (d < 0)
    {
        return 0x49; // if below 0, print "I" of the word "MIN"
    }
    else if(d >= 0 && d < 1000)
    {
        a = d % 10; // a = units digit
        a = a + 0x30;
        return a;
    }
    else if(d >= 1000)
    {
        return 0x41; // if above 3-digits, print "A" of the word "MAX"
    }
}

char dist_ASCII_b2(int d)
{
    int a;
    int b;
    if (d >= 1000 || d < 0)
    {
        return 0x4D; // if below 0 or above 3-digits, print "M" of the word "MAX" or "MIN"
    }
    else if(d >= 0 && d < 1000)
    {
        a = d % 100; // a = rightmost 2 digits
        b = d % 10; // b = units digit
        a = d - b; // tenth digit
        a = a / 10;
        a = a + 0x30;
        return a;
    }
}

char dist_ASCII_b3(int d)
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
        a = a / 100;
        a = a + 0x30;
        return a;
    }
}

int main()
{
    int a = dist_ASCII_b3(250);
    int b = dist_ASCII_b2(250);
    int c = dist_ASCII_b1(250);
    int d = dist_ASCII_b0(250);
    printf("%c%c%c%c", a, b, c, d);
}

