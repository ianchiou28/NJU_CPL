int main()
{
    int num;
    scanf("%x",&num);
    printf("%d\n%u\n%f\n%e",*(int*)&num,*(unsigned int*)&num,*(float*)&num,*(float*)&num);
    return 0;
}