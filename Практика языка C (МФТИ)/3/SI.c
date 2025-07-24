int moveright(int* arr, int key, int last)
{
    for (int i = last; i > 0; --i) {
        if (arr[i - 1] <= key)
            return i;
        arr[i] = arr[i - 1];
    }
    return 0;
}
