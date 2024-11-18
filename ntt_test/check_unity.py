# check prime has root of unity in Z_q

def root_of_unity(num, unity):
    for i in range(2, num):
        if pow(i, 512, num) == 1:
            unity[0] = i
            return True
    return False

q = 2048
n = 256
prime = 2424833
unity = [None]

if root_of_unity(prime, unity):
    print(f"{unity[0]} is a {prime}'s {2*n}-th root of unity in Z_{q}")
