//����YES_LEFT����NO_RIGHT
int biSearch(int l, int r, int val)
{
    int mid, left = l, right = r;
    while(left <= right)
    {
        mid = (left + right) >> 1;
        if(num[mid] >= val)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}


//����YES_RIGHT����NO_LEFT
int biSearch(int l, int r, int val)
{
    int mid, left = l, right = r;
    while(left <= right)
    {
        mid = (left + right) >> 1;
        if(num[mid] > val)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return right;
}
