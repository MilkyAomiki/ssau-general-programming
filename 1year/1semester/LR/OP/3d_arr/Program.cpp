
int main()
{
    int width = 2, height = 2, depth = 2;

    int*** arr = new int**[width];

    for (int i = 0; i < width; i++)
    {
        arr[i] = new int*[height];
        for (int j = 0; j < height; j++)
        {
            arr[i][j] = new int[depth];
        }
    }

    return 0;
}