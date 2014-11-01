# Justin Rohr & Kyle Niewiada
# CIS 343 Project 4
#
# InfixPostfix class contains methods for infix to postfix conversion and
# postfix expression evaluation.

class InfixPostfix
  # converts the infix expression string to postfix expression and returns it
  def infixToPostfix(exprStr)

  end

  # evaluate the postfix string and returns the result
  def evaluatePostfix(exprStr)
    Array stack
    splitStr[] = exprStr.split()
    int count = 0;
    str = splitStr[count]
    while str != null do #str.split(pattern=$;, [limit]) and leaving limit out splits till nil and leaving pattern out splits from ' '
      puts exprStr
      if operand?(str)
        stack.push(str)
      elsif operator?(str)
        y = stack.pop()
        x = stack.pop()
        result = applyOperator(x, y, str)
        stack.push(result)
      end
      str = splitStr[count]
    end
    stack.pop()
  end

  private # subsequent methods are private methods

  # returns true if the input is an operator and false otherwise
  def operator?(str)
    str == '+' or str == '-' or str == '*' or str == '/' or str == '%' or str == '^' or str == '('
  end

  # returns true if the input is an operand and false otherwise
  def operand?(str)
    !operator?(str)
  end

  # returns true if the input is a left parenthesis and false otherwise
  def leftParen?(str)
    str == '('
  end

  # returns true if the input is a right parenthesis and false otherwise
  def rightParen?(str)
    str == ')'
  end

  # returns the stack precedence of the input operator
  def stackPrecedence(operator)
    if operator == '+' or operator == '-'
      return 1
    elsif operator == '*' or operator == '/' or operator == '%'
      return 2
    elsif operator == '^'
      return 3
    elsif operator == '('
      return -1
    end
  end

  # returns the input precedence of the input operator
  def inputPrecedence(operator)
    if operator == '+' or operator == '-'
      return 1
    elsif operator == '*' or operator == '/' or operator == '%'
      return 2
    elsif operator == '^'
      return 4
    elsif operator == '('
      return 5
    end
  end

  # applies the operators to num1 and num2 and returns the result
  def applyOperator(num1, num2, operator)
    num1 operator num2
  end

end # end InfixPostfix class