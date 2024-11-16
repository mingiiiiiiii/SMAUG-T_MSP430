# 26017793 -> 25-bit
# 8380417  -> 23-bit
# 2097152  -> 21-bit 

def is_prime(num):
    if num <= 1:
        return False
    if num == 2:
        return True
    if num % 2 == 0:
        return False
    for i in range(3, int(num**0.5) + 1, 2):
        if num % i == 0:
            return False
    return True

def root_of_unity(num, unity):
    for i in range(2, num):
        if pow(i, 512, num) == 1:
            unity[0] = i
            return True
    return False

def check_low(num):
    if (num & 0xFFFF == 1):
        return True
    return False

q = 2048
mu = 1
n = 256
k = 4

small_range = 2 * q//2 * mu * n * k
# print(small_range) -> 2097152

big_range = small_range + 400000

cnt = small_range
unity = [None]
while cnt < big_range:
    if is_prime(cnt):
        if root_of_unity(cnt, unity) and check_low(cnt):
            print(f"{unity[0]} is a {2*n}-th root of unity in Z_{q}")
            print(f"cnt in hex -> {cnt:#08X}")
    # print(cnt)
    cnt += 1