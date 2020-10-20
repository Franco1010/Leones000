"""
Caso de entrada, el problema es elevar a^b, en c++ esto no se puede hacer porque
no existe un tipo de dato tan grande para enteros, a y b en este caso pueden ser
hasta 1 <= A,B <= 10^100000
5
3 2
4 5
7 4
34534985349875439875439875349875 93475349759384754395743975349573495
34543987529435983745230948023948 3498573497543987543985743989120393097595572309482304
"""

n = int(input())
for i in range(n):
    a, b = list(map(int, input().strip().split(" ")))
    print(pow(a, b, 1000000007))

#----------------------------------------------------------

n = int(input())
for i in range(n):
    a=input().strip().split(" ")
    print(pow(int(a[0]), int(a[1]), 1000000007))
