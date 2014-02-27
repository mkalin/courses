sub to_binary {
    my $number = shift;

    # base case
    return $number if $number == 0 || $number == 1;

    # recursive case
    my $quotient = int($number / 2);
    my $remainder = $number % 2;
    my $binary_number = to_binary($quotient) . $remainder;
}

my $n = 37;
my $b = to_binary($n);
print "$n in decimal is $b in binary\n";
# Output:
#
# 37 in decimal is 100101 in binary
#
# Interpretation of output:
#
#  100101 is 37. 
#  37 is (2 * 18) + 1
#    18 is (2 * 9) + 0
#      9 is (2 * 4) + 1
#       4 is (2 * 2) + 0
#        2 is (2 * 1) + 0
#         1 is 1         1
# 
#  Now read the remainder bits at the end, bottom to top: 100101
#
#  Next we work in binary. Note that removing the rightmost
#  bit in a binary number divides the number by 2
#  just as removing the rightmost decimal numeral from a 
#  decimal number divides the number by 10. In the binary
#  case, the remainder is 0 or 1; in the decimal case, the
#  remainder is one of 0,1,...,8,9. For instance, take 37.
#  Remove the 7 (remainder) to get 3. 37 = 3 * 10 + 7.
#
#  Now do the same in binary. 37 in decimal is 100101 in binary.
#
#  Remove the rightmost bit, 1, to get
#  10010, which is 18 (37 = 18 * 2 + 1)
#
#  10010 is 18. Remove the rightmost bit, 0, to get
#  1001, which is 9 (2 * 9 + 0 = 18)
#
#  1001 is 9. Remove the rightmost bit, 1, to get
#  100, which is 4 (2 * 4 + 1 = 9)
#
#  100 is 4. Remove the rightmost bit, 0, to get
#  10, which is 2 (2 * 2 + 0 = 2)
# 
#  10 is 2. Remove the rightmost bit, 0, to get
#  1, which is 1. This is a base case: 1 in decimal is 1 in binary.

