int ft_round(float num)
{
    int     integer_part;
    float   decimal_part;

    integer_part = (int)num;
    decimal_part = num - integer_part;
    if (decimal_part >= 0.5)
        integer_part++;
    return (integer_part)
}