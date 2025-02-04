class PowerCalculator:
    def __init__(self, base, exponent):
        self.base = base
        self.exponent = exponent

    def calculate_power(self):
        return self._pow(self.base, self.exponent)

    def _pow(self, x, n):
        if n == 0:
            return 1
        if n < 0:
            return 1 / self._pow(x, -n)

        half_power = self._pow(x, n // 2)
        if n % 2 == 0:
            return half_power * half_power
        else:
            return half_power * half_power * x

def main():
    base = float(input("Enter the base (x): "))
    exponent = int(input("Enter the exponent (n): "))
    calculator = PowerCalculator(base, exponent)
    result = calculator.calculate_power()
    print(f"{base} raised to the power of {exponent} is: {result}")

if __name__ == "__main__":
    main()