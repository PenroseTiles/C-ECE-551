int max(int num1, int num2) {
  int max;
  if (num1 > num2) {
    max = num1;
  }
  else {
    max = num2;
  }
  return max;
}

int main(void) {
  printf("max(42, -69) is %d\n", max(42, -69));
  printf("max(33, 0) is %d\n", max(33, 0));
  printf("max(0x123456, 123456) is %d\n", max(0x123456, 123456));
  //print the max of 0x451215AF and 0x913591AF and prints it out as a decimal number
  int left = 0x451215AF;
  int right = 0x913591AF;
  printf("max(0x451215AF, 0x913591AF) is %d\n", max(left, right));
  return 0;
}
