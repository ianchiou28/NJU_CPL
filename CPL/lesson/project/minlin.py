class Calculator:
    def __init__(self):
        self.variables = {}  # Store variable values

    def evaluate(self, expression):
        """Evaluate the expression and handle variables."""
        try:
            # Replace variables in the expression with their values
            for var, value in self.variables.items():
                expression = expression.replace(var, str(value))
            
            # Evaluate the expression
            result = eval(expression)
            return result
        except (NameError, SyntaxError):
            return "Invalid expression"
        except ZeroDivisionError:
            return "Division by zero error"

    def assign_variable(self, name, value):
        """Assign a value to a variable."""
        if name.isalpha():  # Check if the variable name is valid
            self.variables[name] = value
            return f"{name} = {value}"
        else:
            return "Invalid variable name"

    def process_input(self, input_str):
        """Process user input to either evaluate or assign variables."""
        if '=' in input_str:
            parts = input_str.split('=')
            if len(parts) == 2
                var_name = parts[0].strip()
                try:
                    value = float(parts[1].strip())
                    return self.assign_variable(var_name, value)
                except ValueError:
                    return "Invalid value"
            else:
                return "Invalid assignment syntax"
        else:
            return self.evaluate(input_str)


def main():
    calc = Calculator()
    print("Simple Calculator with Variables")
    print("Enter expressions to evaluate or assignments (e.g., x = 5)")
    print("Type 'exit' to quit")

    while True:
        user_input = input("Enter: ").strip()
        if user_input.lower() == 'exit':
            break
        output = calc.process_input(user_input)
        print(output)


if __name__ == "__main__":
    main()
