
bool sys_is_little_endian(void)
{
    int i = 1;
    return (bool)(*(char*)&i);
}

