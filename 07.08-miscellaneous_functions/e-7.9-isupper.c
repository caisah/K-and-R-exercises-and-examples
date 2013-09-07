/* unctions like isupper can be implemented to save space or to save time.
   Explore both possibilities.*/
int isupper(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int isupper(int c)
{
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}

int isupper(int c)
{
    return ((_Ctype[(unsigned char)c] & _UP) != 0);
}
