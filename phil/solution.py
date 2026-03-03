import sys

def solve():
    # Use fast I/O for 10^5 characters
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    MOD = 1000000007
    
    output = []
    for t in range(1, T + 1):
        A = input_data[t]
        n = len(A)
        
        # L and R start at the two middle-most indices
        # For n=3: L=1, R=1. For n=4: L=1, R=2.
        L = (n - 1) // 2
        R = n // 2
        
        s_val = 0
        rem = n
        
        while rem > 0:
            if rem % 2 == 1:
                # ODD CASE: The middle is where L and R would overlap 
                # or the 'active' center. In this logic, it's always A[L].
                bit = int(A[L])
                L -= 1
                # After taking the middle of an odd, L and R are now 
                # pointing to the two bits for the next 'even' step.
            else:
                # EVEN CASE: Compare the bits at L and R
                val_L = int(A[L])
                val_R = int(A[R])
                
                if val_L >= val_R:
                    bit = val_L
                    L -= 1
                else:
                    bit = val_R
                    R += 1
            
            s_val = (s_val * 2 + bit) % MOD
            rem -= 1
            
        output.append(f"Case #{t}: {s_val}")
    
    sys.stdout.write("\n".join(output) + "\n")

if __name__ == "__main__":
    solve()